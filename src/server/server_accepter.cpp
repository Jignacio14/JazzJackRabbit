#include "server_accepter.h"

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
  this->gamesMonitor.removeEndedGames();
  for (auto client = clients.begin(); client != clients.end();) {
    std::unique_ptr<Sender> &current = *client;
    if (!current->is_alive()) {
      current->stop();
      client = clients.erase(client);
    }
    client++;
  }
}

void Accepter::accept() {
  Socket peer = this->skt_aceptator.accept();
  std::unique_ptr<Sender> sender =
      std::make_unique<Sender>(std::move(peer), this->gamesMonitor);
  sender->start();
  clients.push_back(std::move(sender));
}

void Accepter::kill() {
  this->_is_alive = false;
  this->skt_aceptator.shutdown(SHUT_RDWR);
  this->skt_aceptator.close();
  this->killAll();
}

void Accepter::killAll() {
  for (auto &client : clients) {
    client->kill();
  }
  clients.clear();
}

Accepter::~Accepter() {}
