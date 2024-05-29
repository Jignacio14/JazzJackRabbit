
#include "lobby_sender.h"

LobbySender::LobbySender(Socket &socket, bool &was_closed)
    : skt(socket), was_closed(was_closed) {}

void LobbySender::send_selected_game(const std::vector<char> &gamename) {
  uint8_t length = gamename.size();
  skt.sendall_bytewise(&length, sizeof(uint8_t), was_closed);
  skt.sendall_bytewise(gamename.data(), gamename.size(), was_closed);
}
