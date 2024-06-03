
#include "client_sender.h"

ClientSender::ClientSender(std::atomic<bool> &keep_talking,
                           Queue<PlayerStatusDTO> &q, ClientProtocol &protocol)
    : keep_talking((keep_talking)), sender_queue(q), protocol(protocol) {}

void ClientSender::run() {
  try {
    bool was_closed = false;
    while (!was_closed && keep_talking) {
      PlayerStatusDTO status = sender_queue.pop();
      protocol.send_status(was_closed, status);
    }
  } catch (... /*tendriamos que hacer nuestra propia clase*/) {
    // const ClosedQueue& e
    // Close de la cola del sender
  }
  keep_talking = false;
}

ClientSender::~ClientSender() {}
