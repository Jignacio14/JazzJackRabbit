#include "./server_sender.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
#include <cstdint>

#define RESENT_GAME_INFO 1
#define REGISTER_PLAYER 2

Sender::Sender(Socket peer, GamesMonitor &games_monitor_ref)
    : servprot(std::move(peer)), gamesMonitor(games_monitor_ref), error(false) {
}

void Sender::sendGamesOptions() {
  std::unordered_map<std::string, uint16_t> games =
      this->gamesMonitor.getGamesStatus();
  bool result = this->servprot.sendGameInfo(games);
  if (!result) {
    this->error = true;
  }
}

void Sender::registerUser(Queue<BaseDTO *> &receiver_queue) {}

void Sender::setUpPlayerLoop() {
  while (true) {
    uint8_t option = this->servprot.getLobbyOption();
    if (option == RESENT_GAME_INFO) {
      this->sendGamesOptions();
      continue;
    }

    if (option == REGISTER_PLAYER) {

      std::string server_name = this->servprot.getUserLobbyString();
      std::string user_name = this->servprot.getUserLobbyString();
      if (server_name.empty() || user_name.empty()) {
        this->error = true;
        break;
      }
      // this->gamesMonitor.registerUser(server_name, user_name);

      break;
    }

    if (this->error) {
      break;
    }
  }
}

void Sender::run() {
  this->sendGamesOptions();
  this->setUpPlayerLoop();
  if (this->error) {
    this->kill();
    return;
  }
  this->runSenderLoop();
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
