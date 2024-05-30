#include "./server_receiver.h"
#include "./server_protocol.h"

Receiver::Receiver(ServerProtocol &servprot,
                   Queue<PlayerStatusDTO> &receiver_queue)
    : servprot(servprot), receiver_queue(receiver_queue) {}

void Receiver::run() {

  while (this->is_alive()) {
  }
}

void Receiver::kill() { this->_is_alive = false; }

Receiver::~Receiver() {}
