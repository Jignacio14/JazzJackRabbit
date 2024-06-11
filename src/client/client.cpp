
#include "./client.h"
#include "../data/convention.h"
#include "./client_receiver.h"
#include "./client_sender.h"

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
  uint8_t command_to_push = PlayerCommands::MOVE_RIGHT;
  command.push_back(command_to_push);
  std::cout << "Moving right"
            << "\n";
  sender_queue.try_push(command);
}

void Client::move_left() {
  std::vector<uint8_t> command;
  uint8_t command_to_push = PlayerCommands::MOVE_LEFT;
  command.push_back(command_to_push);
  std::cout << "Moving Left"
            << "\n";
  sender_queue.try_push(command);
}

void Client::stop_moving() {
  std::vector<uint8_t> command;
  uint8_t command_to_push = PlayerCommands::STOP_MOVING;
  command.push_back(command_to_push);
  sender_queue.try_push(command);
}

void Client::jump() {
  std::vector<uint8_t> command;
  uint8_t command_to_push = PlayerCommands::JUMP;
  command.push_back(command_to_push);
  sender_queue.try_push(command);
}

void Client::shoot() {
  std::vector<uint8_t> command;
  uint8_t command_to_push = PlayerCommands::SHOOT;
  command.push_back(command_to_push);
  sender_queue.try_push(command);
}

void Client::run() {
  std::vector<uint8_t> command;
  uint8_t command_to_push = PlayerCommands::RUN;
  command.push_back(command_to_push);
  sender_queue.try_push(command);
}

void Client::stop_running() {
  std::vector<uint8_t> command;
  uint8_t command_to_push = PlayerCommands::STOP_RUNNING;
  command.push_back(command_to_push);
  sender_queue.try_push(command);
}

void Client::special_attack() {
  std::vector<uint8_t> command;
  uint8_t command_to_push = PlayerCommands::SPECIAL_ATTACK;
  command.push_back(command_to_push);
  sender_queue.try_push(command);
}

void Client::change_weapon(uint8_t weapon_number) {
  std::vector<uint8_t> command;
  uint8_t command_to_push = PlayerCommands::CHANGE_WEAPON;
  command.push_back(command_to_push);
  command.push_back(weapon_number);
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
