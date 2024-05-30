#include "server_client_handler.h"
#include "server_games_monitor.h"
#include "server_receiver.h"
#include "server_sender.h"

ClientHandler::ClientHandler(Queue<PlayerStatusDTO> sender_queue,
                             Queue<PlayerStatusDTO> &receiver_queue,
                             ServerProtocol servprot, GamesMonitor &monitor_ref)
    : servprot(std::move(servprot)), monitor(monitor_ref),
      receiver_queue(receiver_queue), sender_queue(std::move(sender_queue)),
      sender(this->servprot, this->sender_queue),
      receiver(this->servprot, receiver_queue) {}

void ClientHandler::start() {
  this->receiver.start();
  this->sender.start();
}

const bool ClientHandler::running() {
  return this->receiver.is_alive() && this->sender.is_alive();
}

void ClientHandler::stop() {
  this->servprot.shutdown();
  this->receiver.kill();
  this->receiver.join();
  this->sender.kill();
  this->sender.join();
}

ClientHandler::~ClientHandler() {}