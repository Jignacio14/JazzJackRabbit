#include "./server_receiver.h"
#include "./server_protocol.h"
#include <sys/types.h>

Receiver::Receiver(ServerProtocol &servprot,
                   Queue<CommandCodeDto> &receiver_queue)
    : servprot(servprot), receiver_queue(receiver_queue) {}

void Receiver::run() { this->recevierLoop(); }

void Receiver::recevierLoop() {
  while (this->is_alive()) {
    CommandCodeDto dto = this->servprot.asyncGetEventCode();
    this->receiver_queue.push(dto);
  }
}

void Receiver::kill() { this->_is_alive = false; }

Receiver::~Receiver() {}
