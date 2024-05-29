
#include "lobby_receiver.h"

LobbyReceiver::LobbyReceiver(Socket &socket, bool &was_closed)
    : skt(socket), was_closed(was_closed) {}

GameInfoDto LobbyReceiver::get_game_info() {
  GameInfoDto info;
  skt.recvall_bytewise(&info, sizeof(GameInfoDto), &was_closed);
  return info;
}
