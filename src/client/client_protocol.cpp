
#include "client_protocol.h"

#include <sys/socket.h>

ClientProtocol::ClientProtocol(Socket &&socket) : skt(std::move(socket)) {}

void ClientProtocol::send_commands(bool &was_closed,
                                   const CommandCodeDto command_code_dto) {
  try {
    skt.sendall_bytewise(&command_code_dto, sizeof(CommandCodeDto),
                         &was_closed);
  } catch (const LibError &skt_err) {
    std::cout
        << "Some error ocurred while trying to send a message to the server."
        << std::endl;
  }
}

Snapshot ClientProtocol::receive_snapshot(bool &was_closed) {
  try {
    Snapshot status;
    skt.recvall_bytewise(&status, sizeof(Snapshot), &was_closed);
    return status;
  } catch (const LibError &skt_err) {
    throw LibError(errno, "Some error ocurred while trying to receive a "
                          "message from the server.");
    // throw std::runtime_error("Some error ocurred while trying to receive a
    // message from the server.");
  }
}

void ClientProtocol::close_and_shutdown() {
  skt.shutdown(SHUT_RDWR);
  skt.close();
}
