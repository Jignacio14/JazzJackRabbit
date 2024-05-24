#include "server_protocol.h"

#define HOW 2

ServerProtocol::ServerProtocol(Socket skt) : skt(std::move(skt)) {}

void ServerProtocol::shutdown() {
  this->skt.shutdown(HOW);
  this->skt.close();
}