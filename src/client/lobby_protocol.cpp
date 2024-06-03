
#include "lobby_protocol.h"

LobbyProtocol::LobbyProtocol(Socket &a_skt) : was_closed(false), skt(a_skt) {}

uint16_t LobbyProtocol::receive_header() {
  uint16_t header;
  skt.recvall_bytewise(&header, sizeof(uint8_t), &was_closed);
  header = ntohs(header);
  return header;
}

GameInfoDto LobbyProtocol::receive_game() {
  GameInfoDto single_game_info;
  skt.recvall_bytewise(&single_game_info, sizeof(single_game_info),
                       &was_closed);
  return single_game_info;
}

void LobbyProtocol::send_selected_game(const std::vector<char> &gamename,
                                       uint8_t game_option, char user_character,
                                       const std::vector<char> &username) {
  skt.sendall_bytewise(&game_option, sizeof(uint8_t), &was_closed);
  uint8_t length = gamename.size();
  skt.sendall_bytewise(&length, sizeof(uint8_t), &was_closed);
  skt.sendall_bytewise(gamename.data(), gamename.size(), &was_closed);
  skt.sendall_bytewise(&user_character, sizeof(char), &was_closed);
  skt.sendall_bytewise(username.data(), username.size(), &was_closed);
}

bool LobbyProtocol::wait_game_start() {
  uint16_t len = receive_header();
  std::vector<char> players;
  for (int i = 0; i < len; ++i) {
    char actual;
    skt.recvall_bytewise(&actual, sizeof(char), &was_closed);
    players.push_back(actual);
  }
  return true;
}
