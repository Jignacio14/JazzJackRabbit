#include "server_acceptator.h"

#define HOW 2

Acceptator::Acceptator(const std::string &port) : skt_aceptator(port.c_str()) {}

void Acceptator::run() {
  while (this->is_alive()) {
    this->accept();
  }
}

void Acceptator::accept() { Socket peer = this->skt_aceptator.accept(); }

void Acceptator::kill() {
  this->_is_alive = false;
  this->skt_aceptator.shutdown(HOW);
  this->skt_aceptator.close();
}