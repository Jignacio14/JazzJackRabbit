#include "server_game.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <thread>

#include "../common/global_configs.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static double TICKS_PER_SECOND =
    globalConfigs.getTargetTicksPerSecondOfServer();

const static double SERVER_RATE = ((double)1) / TICKS_PER_SECOND;

const static int MAX_INSTRUCTIONS_PER_TICK =
    globalConfigs.getMaxInstructionsPerTickOfServer();

const static int PLAYER_INITIAL_POSITION_X = 60;
const static int PLAYER_INITIAL_POSITION_Y = 1050;

Game::Game(GameMonitor &monitor, Queue<CommandCodeDto> &queue)
    : monitor(monitor), messages(queue), players(0), snapshot{},
      iterationNumber(0), rate(SERVER_RATE) {}

double Game::now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

void Game::gameLoop() {
  try {
    this->addEnemies();

    while (this->_is_alive) {
      double start = this->now();

      for (auto &pair : players_data) {
        if (pair.second) {
          pair.second->update();
        }
      }

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

void Game::addEnemies() {
  BaseEnemy *enemy = new BaseEnemy(1, snapshot, 0);
  this->enemies.push_back(enemy);
  EnemyDto new_enemy = {};
  new_enemy.entity_id = 1;
  new_enemy.facing_direction = FacingDirectionsIds::Left;
  new_enemy.is_dead = 0;
  new_enemy.was_hurt = 0;
  new_enemy.shot = 0;
  new_enemy.position_x = 500;
  new_enemy.position_y = 1050;
  new_enemy.type = EnemiesIds::Bubba;
  this->snapshot.enemies[this->snapshot.sizeEnemies] = new_enemy;
  this->snapshot.sizeEnemies++;
}

void Game::executeAction(const uint8_t &player_id, const uint8_t &action,
                         const uint8_t &data) {
  switch (action) {
  case PlayerCommands::MOVE_LEFT:
    this->players_data[player_id]->move_left();
    break;
  case PlayerCommands::MOVE_RIGHT:
    this->players_data[player_id]->move_right();
    break;
  case PlayerCommands::STOP_MOVING:
    this->players_data[player_id]->stop_moving();
    break;
  case PlayerCommands::JUMP:
    this->players_data[player_id]->jump();
    break;
    /*
        case PlayerCommands::SHOOT:
          this->players_data[player_id]->shoot();
          break;
        case PlayerCommands::SPECIAL_ATTACK:
          this->players_data[player_id]->specialAttack();
          break; */
  }
}

void Game::run() {
  try {
    this->gameLoop();
  } catch (...) {
    std::cout << "Paso algo en el game loop";
  }
}

BasePlayer *Game::constructPlayer(uint8_t player_id, std::string &player_name,
                                  uint8_t player_type) {
  if (player_type == PlayableCharactersIds::Jazz) {
    return new Jazz(player_id, player_name, snapshot,
                    this->snapshot.sizePlayers);
  }

  if (player_type == PlayableCharactersIds::Lori) {
    return new Lori(player_id, player_name, snapshot,
                    this->snapshot.sizePlayers);
  }

  if (player_type == PlayableCharactersIds::Spaz) {
    return new Spaz(player_id, player_name, snapshot,
                    this->snapshot.sizePlayers);
  }

  return nullptr;
}

void Game::addPlayer(const PlayerInfo &player_info, const uint8_t &player_id) {
  if (this->snapshot.sizePlayers >= MAX_PLAYERS) {
    // No se pueden agregar más jugadores
    return;
  }
  this->players++;
  std::string player_name(player_info.player_name);
  BasePlayer *new_player =
      this->constructPlayer(player_id, player_name, player_info.character_code);
  if (new_player == nullptr) {
    return;
  }
  this->players_data[this->players] = new_player;
  this->addPlayerToSnapshot(player_info);
}

void Game::addPlayerToSnapshot(const PlayerInfo &player_info) {
  PlayerDto new_player_dto;
  new_player_dto.user_id = this->players;
  new_player_dto.points = (uint16_t)globalConfigs.getPlayerStartingPoints();
  new_player_dto.life = (uint8_t)globalConfigs.getPlayerMaxLife();
  new_player_dto.current_gun = GunsIds::Gun1;
  new_player_dto.ammo_gun_1 =
      (uint8_t)globalConfigs.getPlayerStartingAmmoGun1();
  new_player_dto.ammo_gun_2 =
      (uint8_t)globalConfigs.getPlayerStartingAmmoGun2();
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
    delete it->second;
    players_data.erase(it);
    this->players--;
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

void Game::kill() { this->_is_alive = false; }

Game::~Game() {
  for (const auto &pair : players_data) {
    delete pair.second;
  }
  for (const auto &enemy : enemies) {
    delete enemy;
  }
}
