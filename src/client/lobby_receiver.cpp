
#include "lobby_receiver.h"

LobbyReceiver::LobbyReceiver(Socket &socket) : skt(socket) {}

GameInfoDto LobbyReceiver::get_game_info() {
  GameInfoDto info;
  skt.recvall_bytewise(&info, sizeof(GameInfoDto), &was_closed);
}
