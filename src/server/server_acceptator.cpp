#include "server_acceptator.h"

Acceptator::Acceptator(const std::string &port) {}

void Acceptator::run() {
  while (this->is_alive()) {
  }
}

void Acceptator::kill() { this->_is_alive = false; }