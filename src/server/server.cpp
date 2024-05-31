#include "server.h"
#include "server_accepter.h"
#define END_INPUT 'q'

Server::Server(const std::string &port) : acceptator(port.c_str()) {}

void Server::execute() {
  acceptator.start();
  while (std::cin.get() != END_INPUT) {
  }
  acceptator.kill();
  acceptator.join();
}

Server::~Server() {}
