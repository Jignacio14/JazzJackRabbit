#include "./server_sender.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
#include <netinet/in.h>
#include <utility>

Sender::Sender(Socket peer, GamesMonitor &games_monitor_ref)
    : servprot(std::move(peer)), gamesMonitor(games_monitor_ref) {}

void Sender::sendGameInfo() {
  // TO-DO chequear con los chicos que info debo enviar
  // this->servprot.sendGameInfo();
}

void Sender::run() {
  this->sendGameInfo();
  this->runSenderLoop();
}

void Sender::runSenderLoop() {
  while (this->is_alive()) {
  }
}

void Sender::kill() { this->_is_alive = false; }

Sender::~Sender() {}
