#include "./server_sender.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
#include "server_receiver.h"
#include <cstdint>
#include <stdexcept>
#include <sys/types.h>
#include <utility>

#define RESEND_GAME_INFO 1
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

Queue<std::pair<u_int8_t, u_int8_t>> Sender::setUpPlayerLoop() {
  while (true) {
    uint8_t option = this->servprot.getLobbyOption();
    if (option == RESEND_GAME_INFO) {
      this->sendGamesOptions();
      continue;
    }
    if (option == REGISTER_PLAYER) {
      PlayerInfo player_info = this->servprot.getGameInfo();
      this->ValidatePlayerInfo(player_info);
      std::pair<Queue<std::pair<uint8_t, uint8_t>> &, uint8_t> result =
          this->gamesMonitor.registerPlayer(player_info, this->sender_queue);
      this->servprot.sendPlayerId(result.second);
      return std::move(result.first);
    }
  }
}

void Sender::ValidatePlayerInfo(const PlayerInfo &player_info) {
  if (player_info.str_len == 0 || player_info.character_code == 0) {
    this->_is_alive = false;
    throw std::runtime_error("Error en la comunicacion con el cliente");
  }
}

void Sender::run() {
  try {
    this->sendGamesOptions();
    Queue<std::pair<uint8_t, uint8_t>> receiver_queue = this->setUpPlayerLoop();
    Receiver receiver(this->servprot, receiver_queue);
    receiver.start();
    this->runSenderLoop();
    receiver.kill();
    receiver.join();
  } catch (const std::runtime_error &e) {
    this->kill();
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown error" << std::endl;
  }
}

void Sender::runSenderLoop() {
  while (this->is_alive()) {
    Snapshot snapshot = this->sender_queue.pop();
    this->servprot.sendSnapshot(snapshot);
  }
}

void Sender::kill() {
  // this->gamesMonitor.erasePlayer(this->sender_queue);
  this->_is_alive = false;
  this->servprot.shutdown();
}

Sender::~Sender() {}
