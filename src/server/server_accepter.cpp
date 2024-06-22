#include "server_accepter.h"
#include <iostream>

Accepter::Accepter(const std::string &port)
    : skt_aceptator(port.c_str()), clients(), gamesMonitor() {}

void Accepter::run() {
  while (this->is_alive()) {
    this->accept();
    this->checkForDisconnected();
  }
}

void Accepter::checkForDisconnected() {
  try {
    this->gamesMonitor.removeEndedGames();
    this->clients.remove_if([](const std::unique_ptr<Sender> &client) {
      if (!client->is_alive()) {
        client->join();
        return true;
      }
      return false;
    });
  } catch (...) {
    std::cout << "Error al remover clientes desconectados" << std::endl;
    std::cout << "Lo mantengo con vida" << std::endl;
  }
}

void Accepter::accept() {
  try {
    Socket peer = this->skt_aceptator.accept();
    std::unique_ptr<Sender> sender =
        std::make_unique<Sender>(std::move(peer), std::ref(this->gamesMonitor));
    this->clients.push_back(std::move(sender));
    this->clients.back()->start();
  } catch (const LibError &e) {
    this->_is_alive = false;
    return;
  }
}

void Accepter::kill() {
  this->_is_alive = false;
  skt_aceptator.shutdown(2);
  skt_aceptator.close();
  this->killAll();
}

void Accepter::killAll() {
  for (auto &client : this->clients) {
    client->kill();
  }
  this->clients.clear();
}

Accepter::~Accepter() {}
