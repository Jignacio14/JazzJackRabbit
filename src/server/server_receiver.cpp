#include "./server_receiver.h"
#include "./server_protocol.h"
#include <sys/types.h>
#include <utility>

Receiver::Receiver(ServerProtocol &servprot,
                   Queue<std::pair<u_int8_t, u_int8_t>> &receiver_queue)
    : servprot(servprot), receiver_queue(receiver_queue) {}

void Receiver::run() {
  try {
    this->recevierLoop();
  } catch (...) {
  }
}

void Receiver::recevierLoop() {
  while (this->is_alive()) {
    std::pair<u_int8_t, u_int8_t> dto = this->servprot.asyncGetEventCode();
    this->receiver_queue.push(dto);
  }
}

void Receiver::kill() { this->_is_alive = false; }

Receiver::~Receiver() {}
