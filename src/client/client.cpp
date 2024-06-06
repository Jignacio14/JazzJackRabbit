
#include "client.h"
#include "client_receiver.h"
#include "client_sender.h"

Client::Client(Socket &&socket, int id)
    : client_id(id), protocol(std::move(socket)), keep_talking(true),
      sender(keep_talking, sender_queue, protocol),
      receiver(keep_talking, protocol, receiver_queue) {
  receiver.start();
  sender.start();
}

std::optional<Snapshot> Client::get_current_snapshot() {
  Snapshot snapshot;
  if (receiver_queue.try_pop(snapshot)) {
    return std::optional<Snapshot>(snapshot);
  } else {
    return std::optional<Snapshot>();
  }
}

void Client::kill() {
  protocol.close_and_shutdown();
  receiver.kill();
  sender.kill();
  sender.join();
  receiver.join();
}

Client::~Client() {
  protocol.close_and_shutdown();
  this->sender_queue.close();
  this->receiver_queue.close();
  this->receiver.kill();
  this->sender.stop();
  this->receiver.join();
  this->sender.join();
}
