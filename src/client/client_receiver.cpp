
#include "client_receiver.h"

ClientReceiver::ClientReceiver(std::atomic<bool> &keep_talking,
                               ClientProtocol &protocol, Queue<Snapshot> &queue)
    : keep_talking(keep_talking), protocol(protocol), receiver_queue(queue) {}

void ClientReceiver::run() {
  try {
    bool was_closed = false;
    while (!was_closed && keep_talking) {
      Snapshot snapshot;
      snapshot = protocol.receive_snapshot(was_closed);
      receiver_queue.push(snapshot);
    }
  } catch (const ClosedQueue &e) {
    std::cout << "Receiver queue was closed." << std::endl;
  }
  keep_talking = false;
}

void ClientReceiver::kill() { keep_talking = false; }

ClientReceiver::~ClientReceiver() {}
