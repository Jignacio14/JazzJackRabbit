
#include "lobby_protocol.h"

LobbyProtocol::LobbyProtocol(Socket &a_skt) : was_closed(false), skt(a_skt) {}

uint16_t LobbyProtocol::receive_header() {
  uint16_t header;
  skt.recvall_bytewise(&header, sizeof(uint8_t), &was_closed);
  header = ntohs(header);
  this->skt_was_closed();
  return header;
}

GameInfoDto LobbyProtocol::receive_game() {
  try {
    GameInfoDto single_game_info;
    skt.recvall_bytewise(&single_game_info, sizeof(single_game_info),
                         &was_closed);
    this->skt_was_closed();
    return single_game_info;
  } catch (const std::exception &err) {
    std::cout << "Some error ocurred while trying to receive a message from "
                 "the server."
              << std::endl;
    throw std::runtime_error(
        "Some error ocurred while trying to receive a message from "
        "the server.");
  }
}

void LobbyProtocol::send_selected_game(const std::vector<char> &gamename,
                                       uint8_t game_option, char user_character,
                                       const std::vector<char> &username) {
  try {
    skt.sendall_bytewise(&game_option, sizeof(uint8_t), &was_closed);
    uint8_t length = gamename.size();
    skt.sendall_bytewise(&length, sizeof(uint8_t), &was_closed);
    skt.sendall_bytewise(gamename.data(), gamename.size(), &was_closed);
    skt.sendall_bytewise(&user_character, sizeof(char), &was_closed);
    skt.sendall_bytewise(username.data(), username.size(), &was_closed);
    this->skt_was_closed();
  } catch (const std::exception &err) {
    std::cout
        << "Some error ocurred while trying to send a message to the server."
        << std::endl;
  }
}

void LobbyProtocol::send_refresh() {
  try {
    uint8_t refresh = REFRESH;
    skt.sendall_bytewise(&refresh, sizeof(uint8_t), &was_closed);
    this->skt_was_closed();
  } catch (const std::exception &err) {
    std::cout
        << "Some error ocurred while trying to send a message to the server."
        << std::endl;
  }
}

bool LobbyProtocol::wait_game_start() {
  try {
    uint16_t len = receive_header();
    std::vector<char> players;
    for (int i = 0; i < len; ++i) {
      char actual;
      skt.recvall_bytewise(&actual, sizeof(char), &was_closed);
      players.push_back(actual);
    }
    this->skt_was_closed();
    return true;
  } catch (const std::exception &err) {
    std::cout << "Some error ocurred while trying to receive a message from "
                 "the server."
              << std::endl;
    return false;
  }
}

void LobbyProtocol::skt_was_closed() {
  if (was_closed) {
    throw std::runtime_error(
        "The socket was closed and the communication failed.");
  }
}
