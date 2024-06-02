#include "./server_sender.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
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

// Queue<BaseDTO *> &Sender::setUpPlayerLoop() {
// std::string server_name = "";
// std::string user_name = "";
// while (true) {
//   uint8_t option = this->servprot.getLobbyOption();
//   if (option == RESENT_GAME_INFO) {
//     this->sendGamesOptions();
//     continue;
//   }
//   if (option == REGISTER_PLAYER) {
//     std::pair<std::string, std::string> data =
//         this->servprot.getGameNameAndPlayerName();
//     server_name = data.first;
//     user_name = data.second;
//     if (server_name.empty() || user_name.empty()) {

//       this->error = true;
//       throw std::runtime_error("Error en la comunicacion con el cliente");
//     }
//     // this->gamesMonitor.getReceiverQueue(server_name);
//     break;
//   }
// }
// if (this->error) {
//   throw std::runtime_error("Error en la comunicacion con el cliente");
// }
// return this->gamesMonitor.getReceiverQueue("server_name");
// }

void Sender::run() {
  try {
    this->sendGamesOptions();
    const Queue<BaseDTO *> &receiver_queue = this->setUpPlayerLoop();
    this->runSenderLoop();
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
