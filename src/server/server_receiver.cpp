#include "./server_receiver.h"
#include "./server_protocol.h"

Receiver::Receiver(ServerProtocol &servprot) : servprot(servprot) {}

void Receiver::run() {

  while (this->is_alive()) {
  }
}

void Receiver::kill() { this->_is_alive = false; }

Receiver::~Receiver() {}
