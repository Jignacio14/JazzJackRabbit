
#include "client_protocol.h"

ClientProtocol::ClientProtocol(Socket &&socket)
    : skt(std::move(socket)), was_closed(false) {}

void ClientProtocol::send_status(bool &was_closed, PlayerStatusDTO status) {
  skt.sendall_bytewise(&status, sizeof(PlayerStatusDTO), &was_closed);
}

void ClientProtocol::receive_snapshot(bool &was_closed, Snapshot &snapshot) {
  skt.recvall_bytewise(&snapshot, sizeof(Snapshot), &was_closed);
}

void ClientProtocol::close_and_shutdown() {
  skt.close();
  skt.shutdown(SHUT_RDWR);
}
