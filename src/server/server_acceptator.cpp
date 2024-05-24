#include "server_acceptator.h"
#include "server_client_handler.h"

#define HOW 2

Acceptator::Acceptator(const std::string &port)
    : skt_aceptator(port.c_str()), clients() {}

void Acceptator::run() {
  while (this->is_alive()) {
    this->accept();
    this->checkForDisconnected();
  }
}

void Acceptator::checkForDisconnected() {
  for (auto client = clients.begin(); client != clients.end();) {
    ClientHandler *current = *client;
    if (!current->running()) {
      current->stop();
      delete current;
      client = clients.erase(client);
    }
    client++;
  }
}

void Acceptator::accept() {
  Socket peer = this->skt_aceptator.accept();
  ClientHandler *handler = new ClientHandler(std::move(peer));
  clients.push_back(handler);
  handler->start();
}

void Acceptator::kill() {
  this->_is_alive = false;
  this->skt_aceptator.shutdown(HOW);
  this->skt_aceptator.close();
}