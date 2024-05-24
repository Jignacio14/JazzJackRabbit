#include "server_client_handler.h"
#include "server_receiver.h"
#include "server_sender.h"

ClientHandler::ClientHandler(Socket skt)
    : servprot(std::move(skt)), receiver(servprot), sender(servprot) {}

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