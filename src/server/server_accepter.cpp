#include "server_accepter.h"

#define HOW 2

Accepter::Accepter(const std::string &port)
    : skt_aceptator(port.c_str()), clients(), gamesMonitor() {}

void Accepter::run() {
  try {
    while (this->is_alive()) {
      this->accept();
      this->checkForDisconnected();
    }
  } catch (const std::exception &err) {
  }
}

void Accepter::checkForDisconnected() {
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

void Accepter::accept() {
  Socket peer = this->skt_aceptator.accept();
  ClientHandler *handler =
      new ClientHandler(std::move(peer), this->gamesMonitor);
  clients.push_back(handler);
  handler->start();
}

void Accepter::kill() {
  this->_is_alive = false;
  this->skt_aceptator.shutdown(HOW);
  this->skt_aceptator.close();
  this->killAll();
}

void Accepter::killAll() {
  for (auto client : clients) {
    client->stop();
    delete client;
  }
}