#include "./server_receiver.h"
#include "./server_protocol.h"

Receiver::Receiver(ServerProtocol &servprot, Queue<BaseDTO *> &receiver_queue)
    : servprot(servprot), receiver_queue(receiver_queue) {}

void Receiver::run() {
  while (this->is_alive()) {
    BaseDTO *dto;
    // BaseDTO *dto = this->servprot.receive(dto);
    // cppcheck-suppress uninitvar
    if (dto == nullptr) {
      continue;
    }
    this->receiver_queue.try_pop(dto);
  }
}

void Receiver::kill() { this->_is_alive = false; }

Receiver::~Receiver() {}
