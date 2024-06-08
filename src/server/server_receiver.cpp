#include "./server_receiver.h"
#include "./server_protocol.h"

Receiver::Receiver(ServerProtocol &servprot, Queue<Snapshot> &receiver_queue)
    : servprot(servprot), receiver_queue(receiver_queue) {}

void Receiver::run() {
  while (this->is_alive()) {
    // BaseDTO *dto = this->servprot.receive(dto);
    // cppcheck-suppress uninitvar
    // this->receiver_queue.try_pop(dto);
  }
}

void Receiver::kill() { this->_is_alive = false; }

Receiver::~Receiver() {}
