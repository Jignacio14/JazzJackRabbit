#include "server_game.h"
#include <cstring>
#include <exception>
#include <iostream>
#include <thread>

#include "../common/global_configs.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

static GlobalCounter &counter = GlobalCounter::getInstance();

const static double TICKS_PER_SECOND =
    globalConfigs.getTargetTicksPerSecondOfServer();

const static double SERVER_RATE = ((double)1) / TICKS_PER_SECOND;

const static int MAX_INSTRUCTIONS_PER_TICK =
    globalConfigs.getMaxInstructionsPerTickOfServer();

const static double GAME_DURATION = globalConfigs.getMaxGameDuration();

const static int PLAYER_INITIAL_POSITION_X = 60;
const static int PLAYER_INITIAL_POSITION_Y = 1050;

const static double GAME_DURATION_CHEAT = 2;

Game::Game(GameMonitor &monitor, Queue<CommandCodeDto> &queue)
    : monitor(monitor), messages(queue), players(0), snapshot{},
      gameEnded(false), iterationNumber(0), rate(SERVER_RATE),
      collectablesHandler(collectables, snapshot),
      enemiesHandler(enemies, snapshot), cheat2Activated(false) {}

double Game::now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

void Game::gameLoop() {
  try {
    this->snapshot.sizePlayers = players;
    this->snapshot.sizeEnemies = 0;
    this->snapshot.sizeCollectables = 0;
    this->snapshot.sizeBullets = 0;
    this->snapshot.timeLeft = GAME_DURATION;
    this->snapshot.gameEnded = NumericBool::False;

    collectablesHandler.initialize();

    enemiesHandler.initialize();

    double initTimestamp = this->now();

    while (this->_is_alive) {
      double start = this->now();
      if (cheat2Activated) {
        this->snapshot.timeLeft =
            GAME_DURATION_CHEAT - ((start - initTimestamp) / 1000);
      } else {
        this->snapshot.timeLeft =
            GAME_DURATION - ((start - initTimestamp) / 1000);
      }

      if (this->snapshot.timeLeft < 0) {
        this->snapshot.gameEnded = NumericBool::True;
        this->gameEnded = true;
        this->snapshot.timeLeft = (double)0;
        this->_is_alive = false;
      }

      this->updatePlayers();

      this->updateCollectables();

      enemiesHandler.update();

      this->updateEnemies();

      this->updateBullets();

      CommandCodeDto command;
      int instructions_count = 0;
      while (instructions_count < MAX_INSTRUCTIONS_PER_TICK) {
        bool has_command = messages.try_pop(command);

        if (has_command) {
          uint8_t player_id = command.player_id;
          uint8_t action = command.code;
          uint8_t data = command.data;
          this->executeAction(player_id, action, data);

        } else {
          break;
        }
        instructions_count++;
      }

      this->monitor.broadcast(snapshot);
      double finish = this->now();
      this->rateController(start, finish);
    }
  } catch (const ClosedQueue &e) {
    std::cout << "Messages queue was closed." << std::endl;
  } catch (...) {
    std::cout << "Error in game loop." << std::endl;
  }
}

void Game::rateController(double start, double finish) {
  double timeToRest = rate - (finish - start);

  if (timeToRest < 0) {
    double behind = -timeToRest;
    timeToRest = rate - fmod(behind, rate);
    double lost = behind + timeToRest;
    iterationNumber += std::floor(lost / rate);

  } else {
    std::this_thread::sleep_for(std::chrono::duration<double>(timeToRest));
    iterationNumber++;
  }
}

void Game::run() {
  try {
    this->gameLoop();
  } catch (...) {
    std::cout << "Error in game loop." << std::endl;
  }
}

std::unique_ptr<BasePlayer> Game::constructPlayer(uint8_t player_id,
                                                  std::string &player_name,
                                                  uint8_t player_type) {
  if (player_type == PlayableCharactersIds::Jazz) {
    return std::make_unique<Jazz>(player_id, player_name, snapshot, 0, map);
  }

  if (player_type == PlayableCharactersIds::Lori) {
    return std::make_unique<Lori>(player_id, player_name, snapshot, 0, map);
  }

  if (player_type == PlayableCharactersIds::Spaz) {
    return std::make_unique<Spaz>(player_id, player_name, snapshot, 0, map);
  }

  return nullptr;
}

void Game::executeAction(const uint8_t &player_id, const uint8_t &action,
                         const uint8_t &data) {
  switch (action) {
  case PlayerCommands::MOVE_LEFT:
    this->players_data[player_id]->move_left(WALKING_SPEED);
    break;
  case PlayerCommands::MOVE_RIGHT:
    this->players_data[player_id]->move_right(WALKING_SPEED);
    break;
  case PlayerCommands::STOP_MOVING:
    this->players_data[player_id]->stop_moving();
    break;
  case PlayerCommands::JUMP:
    this->players_data[player_id]->jump();
    break;
  case PlayerCommands::RUN:
    this->players_data[player_id]->run();
    break;
  case PlayerCommands::STOP_RUNNING:
    this->players_data[player_id]->stop_running();
    break;
  case PlayerCommands::SHOOT: {
    Bullet newBullet = this->players_data[player_id]->shoot();
    if (newBullet.get_damage() > INVALID_DAMAGE) {
      bullets.push_back(newBullet);
    }
    break;
  }
  case PlayerCommands::CHANGE_WEAPON:
    this->players_data[player_id]->change_weapon(data);
    break;
  case PlayerCommands::CHEAT_1:
    collectablesHandler.reset_collectables();
    break;
  case PlayerCommands::CHEAT_2:
    this->cheat2Activated = true;
    snapshot.timeLeft = GAME_DURATION_CHEAT;
    break;
  case PlayerCommands::SPECIAL_ATTACK:
    this->players_data[player_id]->special_attack();
    break;
  }
}

void Game::addPlayer(const PlayerInfo &player_info, const uint8_t &player_id) {
  if (this->snapshot.sizePlayers >= MAX_PLAYERS) {
    return;
  }
  this->players++;
  std::string player_name(player_info.player_name);
  std::unique_ptr<BasePlayer> new_player =
      this->constructPlayer(player_id, player_name, player_info.character_code);
  if (new_player == nullptr) {
    return;
  }
  this->players_data[this->players] = std::move(new_player);
  this->addPlayerToSnapshot(player_info);
}

void Game::addPlayerToSnapshot(const PlayerInfo &player_info) {
  PlayerDto new_player_dto;
  new_player_dto.user_id = this->players;

  new_player_dto.nameSize = player_info.str_len;

  int i = 0;
  for (i = 0; i < player_info.str_len; i++) {
    new_player_dto.name[i] = player_info.player_name[i];
  }
  new_player_dto.name[i] = '\0';

  new_player_dto.points = (uint32_t)globalConfigs.getPlayerStartingPoints();
  new_player_dto.life = (uint16_t)globalConfigs.getPlayerMaxLife();
  new_player_dto.current_gun = GunsIds::Gun1;
  new_player_dto.ammo_gun_1 =
      (uint16_t)globalConfigs.getPlayerStartingAmmoGun1();
  new_player_dto.ammo_gun_2 =
      (uint16_t)globalConfigs.getPlayerStartingAmmoGun2();
  new_player_dto.type = player_info.character_code;
  new_player_dto.is_falling = NumericBool::False;
  new_player_dto.is_jumping = NumericBool::False;
  new_player_dto.is_walking = NumericBool::False;
  new_player_dto.is_running = NumericBool::False;
  new_player_dto.facing_direction = FacingDirectionsIds::Right;
  new_player_dto.is_intoxicated = NumericBool::False;
  new_player_dto.shot = NumericBool::False;
  new_player_dto.shot_special = NumericBool::False;
  new_player_dto.is_dead = NumericBool::False;
  new_player_dto.was_hurt = NumericBool::False;
  new_player_dto.position_x = PLAYER_INITIAL_POSITION_X;
  new_player_dto.position_y = PLAYER_INITIAL_POSITION_Y;

  this->snapshot.players[this->snapshot.sizePlayers] = new_player_dto;
  this->snapshot.sizePlayers++;
}

void Game::ereasePlayer(uint8_t player_id) {
  // this->monitor.ereasePlayer(this->messages);
  auto it = players_data.find(player_id);
  if (it != players_data.end()) {
    players_data.erase(it);
    this->players--;
  }

  if (this->players == 0) {
    this->gameEnded = true;
    this->_is_alive = false;
  }

  bool playerFound = false;
  for (int i = 0; i < this->snapshot.sizePlayers; ++i) {
    if (this->snapshot.players[i].user_id == player_id) {
      playerFound = true;
      for (int j = i; j < this->snapshot.sizePlayers - 1; ++j) {
        this->snapshot.players[j] = this->snapshot.players[j + 1];
      }
      break;
    }
  }

  if (playerFound) {
    this->snapshot.sizePlayers--;
    memset(&this->snapshot.players[this->snapshot.sizePlayers], 0,
           sizeof(PlayerDto));
  }
}

void Game::handleEnemyDiedByBullet(bool died, Bullet bullet, BaseEnemy &enemy) {
  if (died) {
    uint8_t id_player_who_shot = bullet.get_player_id();
    auto it = players_data.find(id_player_who_shot);
    if (it != players_data.end()) {
      it->second->add_points(enemy.get_points());
    }
  }
}

void Game::updateBullets() {
  for (auto &bullet : bullets) {
    bullet.move(snapshot);
    for (auto &pair : players_data) {
      auto &player = pair.second;
      if (player->intersects(bullet.get_rectangle()) && player->is_alive()) {
        player->receive_damage(bullet.get_damage());
        bullet.kill(snapshot);
        break;
      }
    }
    for (auto &enemy : enemies) {
      if (enemy->intersects(bullet.get_rectangle()) && enemy->is_alive()) {
        bool enemy_died = false;
        uint8_t drop = enemy->receive_damage(bullet.get_damage(), enemy_died);
        this->handleEnemyDiedByBullet(enemy_died, bullet, *enemy);
        Rectangle drop_rectangle = enemy->drop_rectangle();
        this->handleDrop(drop, drop_rectangle);
        bullet.kill(snapshot);
        break;
      }
    }
  }
  bullets.erase(
      std::remove_if(bullets.begin(), bullets.end(),
                     [](Bullet &bullet) { return !bullet.is_alive(); }),
      bullets.end());
}

void Game::updateEnemies() {
  for (auto &enemy : enemies) {
    for (auto &pair : players_data) {
      auto &player = pair.second;
      if (enemy->intersects_with_direction(player->get_rectangle()) &&
          enemy->can_attack()) {
        enemy->attack(*player);
        break;
      }
    }
  }
}

void Game::updatePlayers() {
  for (auto &attacker_pair : players_data) {
    auto &attacker = attacker_pair.second;
    attacker->update();
    if (attacker->is_doing_special_attack()) {
      for (auto &enemy : enemies) {
        if (enemy->intersects(attacker->get_rectangle()) && enemy->is_alive()) {
          bool enemy_died = false;
          uint8_t drop = enemy->receive_damage(
              attacker->get_special_attack_damage(), enemy_died);
          Rectangle drop_rectangle = enemy->drop_rectangle();
          this->handleDrop(drop, drop_rectangle);
          if (enemy_died) {
            attacker->add_points(enemy->get_points());
          }
          break;
        }
      }
      for (auto &defender_pair : players_data) {
        auto &defender = defender_pair.second;
        if (attacker != defender &&
            defender->intersects(attacker->get_rectangle())) {
          defender->receive_damage(attacker->get_special_attack_damage());
        }
      }
    }
  }
}

void Game::handleDrop(uint8_t drop, Rectangle drop_rectangle) {
  if (drop == EnemyDrop::NoDrop) {
    return;
  }
  switch (drop) {
  case EnemyDrop::Ammo:
    collectablesHandler.add_ammo(drop_rectangle);
    break;
  case EnemyDrop::Carrot:
    collectablesHandler.add_carrot(drop_rectangle);
    break;
  }
}

void Game::updateCollectables() {
  for (auto &collectable : collectables) {
    for (auto &pair : players_data) {
      auto &player = pair.second;
      if (player->intersects(collectable->get_rectangle())) {
        collectable->collect(*player);
        break;
      }
    }
  }

  collectables.erase(
      std::remove_if(collectables.begin(), collectables.end(),
                     [](const std::unique_ptr<BaseCollectable> &collectable) {
                       return collectable->get_collected();
                     }),
      collectables.end());

  if (collectables.size() == 0) {
    collectablesHandler.reset_collectables();
  }
}

void Game::kill() { this->_is_alive = false; }

bool Game::didGameEnd() { return this->gameEnded; };

Game::~Game() {
  try {
    if (this->_is_alive) {
      this->kill();
    }
    this->join();
  } catch (const std::exception &e) {
  }
}
