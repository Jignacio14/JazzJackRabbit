#include "./server_sender.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
#include <cstdint>
#include <stdexcept>
#include <sys/types.h>
#include <utility>

#define RESENT_GAME_INFO 1
#define REGISTER_PLAYER 2

Sender::Sender(Socket peer, GamesMonitor &games_monitor_ref)
    : servprot(std::move(peer)), gamesMonitor(games_monitor_ref), error(false) {
}

void Sender::sendGamesOptions() {
  std::unordered_map<std::string, uint16_t> games =
      this->gamesMonitor.getGamesStartInfo();
  if (!this->servprot.sendGameInfo(games)) {
    throw std::runtime_error("Error en la comunicacion con el cliente");
  }
}

void Sender::registerUser(Queue<BaseDTO *> &receiver_queue) {}

Queue<BaseDTO *> &Sender::setUpPlayerLoop() {
  while (true) {
    uint8_t option = this->servprot.getLobbyOption();
    if (option == RESENT_GAME_INFO) {
      this->sendGamesOptions();
      continue;
    }
    if (option == REGISTER_PLAYER) {
      PlayerInfo player_info = this->servprot.getGameInfo();
      this->ValidatePlayerInfo(player_info);
      std::pair<Queue<BaseDTO *> &, uint8_t> result =
          this->gamesMonitor.registerPlayer(player_info, this->sender_queue);
      this->servprot.sendPlayerId(result.second);
      return result.first;
    }
  }
}

void Sender::ValidatePlayerInfo(const PlayerInfo &player_info) {
  if (player_info.game_name.empty() || player_info.player_name.empty() ||
      player_info.character_code == 0) {
    this->_is_alive = false;
    throw std::runtime_error("Error en la comunicacion con el cliente");
  }
}

void Sender::run() {
  try {
    this->sendGamesOptions();
    const Queue<BaseDTO *> &receiver_queue = this->setUpPlayerLoop();
    this->runSenderLoop();
  } catch (const std::runtime_error &e) {
    this->kill();
  } catch (...) {
  }
}

void Sender::runSenderLoop() {
  while (this->is_alive()) {
  }
}

void Sender::kill() {
  this->_is_alive = false;
  this->servprot.shutdown();
}

Sender::~Sender() {}
