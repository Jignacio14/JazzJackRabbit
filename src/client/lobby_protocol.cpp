
#include "lobby_protocol.h"

LobbyProtocol::LobbyProtocol(Socket &a_skt) : skt(a_skt), was_closed(false) {}

uint8_t LobbyProtocol::receive_number_of_games() {
  uint8_t number_of_games;
  skt.recvall_bytewise(&number_of_games, sizeof(uint8_t), &was_closed);
  return number_of_games;
}

GameInfoDto LobbyProtocol::receive_game() {
  GameInfoDto single_game_info;
  skt.recvall_bytewise(&single_game_info, sizeof(single_game_info),
                       &was_closed);
  return single_game_info;
}

void LobbyProtocol::send_selected_game(const std::vector<char> &gamename) {
  uint8_t length = gamename.size();
  skt.sendall_bytewise(&length, sizeof(uint8_t), &was_closed);
  skt.sendall_bytewise(gamename.data(), gamename.size(), &was_closed);
}
