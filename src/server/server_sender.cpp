#include "server_sender.h"
#include "server_protocol.h"

Sender::Sender(ServerProtocol &servprot) : servprot(servprot) {}

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