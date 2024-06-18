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

  this->clients.remove_if([](const std::unique_ptr<Sender> &client) {
    if (!client->is_alive()) {
      client->stop();
      return true;
    }
    return false;
  });
}

void Accepter::accept() {
  Socket peer = this->skt_aceptator.accept();
  std::unique_ptr<Sender> sender =
      std::make_unique<Sender>(std::move(peer), std::ref(this->gamesMonitor));

  this->clients.push_back(std::move(sender));
  this->clients.back()->start();
}

void Accepter::kill() {
  this->_is_alive = false;
  this->skt_aceptator.shutdown(SHUT_RDWR);
  this->skt_aceptator.close();
  this->killAll();
}

void Accepter::killAll() {
  for (auto &client : this->clients) {
    client->kill();
  }
  this->clients.clear();
}

Accepter::~Accepter() {}
