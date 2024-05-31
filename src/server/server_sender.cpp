#include "./server_sender.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
#include <cstdint>

#define RESENT_GAME_INFO 1
#define REGISTER_PLAYER 2

Sender::Sender(Socket peer, GamesMonitor &games_monitor_ref)
    : servprot(std::move(peer)), gamesMonitor(games_monitor_ref) {}

void Sender::sendGamesOptions() {
  std::unordered_map<std::string, uint16_t> games =
      this->gamesMonitor.getGamesStatus();
  this->servprot.sendGameInfo(games);
}

void Sender::registerUser() {
  // std::string server_name = this->servprot.getUserLobbyString();
  // std::string user_name = this->servprot.getUserLobbyString();
}

void Sender::setUpPlayerLoop() {
  while (true) {
    uint8_t option = this->servprot.getLobbyOption();
    if (option == RESENT_GAME_INFO) {
      this->sendGamesOptions();
      continue;
    }

    if (option == REGISTER_PLAYER) {
      this->registerUser();
      break;
    }
  }
}

void Sender::run() {
  this->sendGamesOptions();
  this->setUpPlayerLoop();
}

// void Sender::runSenderLoop() {
//   while (this->is_alive()) {
//   }
// }

void Sender::kill() {
  this->_is_alive = false;
  this->servprot.shutdown();
}

Sender::~Sender() {}
