#include "./server_receiver.h"
#include "./server_protocol.h"
#include <sys/types.h>
#include <utility>

Receiver::Receiver(ServerProtocol &servprot,
                   Queue<std::pair<u_int8_t, u_int8_t>> &receiver_queue)
    : servprot(servprot), receiver_queue(receiver_queue) {}

void Receiver::run() {
  while (this->is_alive()) {
    // BaseDTO *dto = this->servprot.receive(dto);
    // cppcheck-suppress unreadVariable
    std::pair<u_int8_t, u_int8_t> dto = this->servprot.asyncGetEventCode();
    if (dto.first) {
    } // Just for the compiler not to complain of unused variable
    // this->receiver_queue.try_pop(dto);
  }
}

void Receiver::kill() { this->_is_alive = false; }

Receiver::~Receiver() {}
