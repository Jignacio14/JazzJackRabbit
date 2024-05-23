#include "server_receiver.h"
#include "server_protocol.h"

Receiver::Receiver(const ServerProtocol &servprot) : servprot(servprot) {}

void Receiver::run() {

  while (this->is_alive()) {
  }
}

Receiver::~Receiver() {}