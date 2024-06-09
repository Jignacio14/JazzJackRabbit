
#include "client.h"
#include "client_receiver.h"
#include "client_sender.h"

Client::Client(Socket &&socket, int id)
    : client_id(id), protocol(std::move(socket)), keep_talking(true),
      sender(keep_talking, sender_queue, protocol, id),
      receiver(keep_talking, protocol, receiver_queue) {
  receiver.start();
  sender.start();
}

std::unique_ptr<Snapshot> Client::get_current_snapshot() {
  Snapshot snapshot;
  if (receiver_queue.try_pop(snapshot)) {
    return std::make_unique<Snapshot>(snapshot);
  } else {
    return nullptr;
  }
}

void Client::move_right() {
  std::vector<uint8_t> command;
  command.push_back(PlayerCommands::MOVE_RIGHT);
  sender_queue.try_push(command);
}

void Client::move_left() {
  std::vector<uint8_t> command;
  command.push_back(PlayerCommands::MOVE_LEFT);
  sender_queue.try_push(command);
}

void Client::jump() {
  std::vector<uint8_t> command;
  command.push_back(PlayerCommands::JUMP);
  sender_queue.try_push(command);
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
