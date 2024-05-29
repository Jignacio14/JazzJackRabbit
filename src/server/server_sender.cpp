#include "server_sender.h"
#include "server_protocol.h"

Sender::Sender(const ServerProtocol &servprot) : servprot(servprot) {}

void Sender::run() {
  while (this->is_alive()) {
  }
}

void Sender::kill() { this->_is_alive = false; }