
#include "client_receiver.h"

ClientReceiver::ClientReceiver(std::atomic<bool> &keep_talking,
                               ClientProtocol &protocol, Queue<Snapshot> &queue)
    : keep_talking(keep_talking), protocol(protocol), receiver_queue(queue) {}

void ClientReceiver::run() {
  try {
    bool was_closed = false;
    while (!was_closed && keep_talking) {
      Snapshot snapshot;
      protocol.receive_snapshot(was_closed, snapshot);
    }
  } catch (... /*Nuestra clase manejadora de errores*/) {
    // close de la queue del receiver
  }
  keep_talking = false;
}

ClientReceiver::~ClientReceiver() {}
