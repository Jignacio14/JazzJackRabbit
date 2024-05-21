
#include "client_sender.h"

ClientSender::ClientSender(std::atomic<bool> &keep_talking,
                           Queue<PlayerStatusDTO> &q, Socket &skt)
    : keep_talking((keep_talking)), sender_queue(q), skt(skt) {}

void ClientSender::run() {
  try {
    bool was_closed = false;
    while (!was_closed && keep_talking) {
      PlayerStatusDTO status = sender_queue.pop();
      skt.sendall_bytewise(&status, sizeof(PlayerStatusDTO), &was_closed);
    }
  } catch (... /*tendriamos que hacer nuestra propia clase*/) {
    // const ClosedQueue& e
    // Close de la cola del sender
  }
  keep_talking = false;
}
