
#include "client_protocol.h"

#include <sys/socket.h>

ClientProtocol::ClientProtocol(Socket &&socket) : skt(std::move(socket)) {}

void ClientProtocol::send_status(bool &was_closed,
                                 const std::vector<uint8_t> &command) {
  skt.sendall_bytewise(command.data(), command.size(), &was_closed);
}

Snapshot ClientProtocol::receive_snapshot(bool &was_closed) {
  Snapshot status;
  skt.recvall_bytewise(&status, sizeof(Snapshot), &was_closed);
  return status;
}

void ClientProtocol::send_id(bool &was_closed, const uint8_t id) {
  skt.sendall_bytewise(&id, sizeof(uint8_t), &was_closed);
}

void ClientProtocol::close_and_shutdown() {
  skt.shutdown(SHUT_RDWR);
  skt.close();
}
