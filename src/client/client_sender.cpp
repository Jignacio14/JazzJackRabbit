
#include "client_sender.h"

ClientSender::ClientSender(std::atomic<bool> &keep_talking,
                           Queue<std::vector<uint8_t>> &q,
                           ClientProtocol &protocol, uint8_t id)
    : keep_talking((keep_talking)), sender_queue(q), protocol(protocol),
      id(id) {}

void ClientSender::run() {
  try {
    bool was_closed = false;
    while (!was_closed && keep_talking) {
      std::vector<uint8_t> command = sender_queue.pop();
      protocol.send_id(was_closed, this->id);
      protocol.send_status(was_closed, command);
    }
  } catch (const std::runtime_error &e) {
    std::cout << "Sender queue was closed." << std::endl;
  }
  keep_talking = false;
}

void ClientSender::kill() { keep_talking = false; }

ClientSender::~ClientSender() {}
