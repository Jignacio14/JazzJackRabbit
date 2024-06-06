
#include "client_protocol.h"

#include <sys/socket.h>

ClientProtocol::ClientProtocol(Socket &&socket) : skt(std::move(socket)) {}

void ClientProtocol::send_status(bool &was_closed,
                                 const std::vector<uint8_t> &command) {
  skt.sendall_bytewise(comand.data(), command.size(), &was_closed);
}

Snapshot ClientProtocol::receive_snapshot(bool &was_closed) {
  Snapshot status;
  skt.recvall_bytewise(&status, sizeof(Snapshot), &was_closed);
  return status;
}

void ClientProtocol::close_and_shutdown() {
  skt.shutdown(SHUT_RDWR);
  skt.close();
}
