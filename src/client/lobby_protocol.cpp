
#include "lobby_protocol.h"
#include <cstdint>

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

uint8_t LobbyProtocol::receive_player_id() {
  try {
    uint8_t player_id;
    skt.recvall_bytewise(&player_id, sizeof(uint8_t), &was_closed);
    this->skt_was_closed();
    return player_id;
  } catch (const std::exception &err) {
    std::cout << "Some error ocurred while trying to receive a message from "
                 "the server."
              << std::endl;
    return ERROR;
  }
}

uint8_t
LobbyProtocol::send_selected_game(const std::vector<char> &gamenameToSend,
                                  char user_character,
                                  const std::vector<char> &usernameToSend) {
  try {
    uint8_t game_option = NEW_GAME;
    skt.sendall_bytewise(&game_option, sizeof(uint8_t), &was_closed);
    PlayerInfo player_info;

    player_info.character_code = user_character;
    player_info.str_len = (uint16_t)usernameToSend.size();

    size_t i = 0;
    for (i = 0; i < usernameToSend.size(); i++) {
      player_info.player_name[i] = usernameToSend.at(i);
    }
    player_info.player_name[i] = '\0';
    i++;

    for (size_t j = i; j < usernameToSend.size(); j++) {
      player_info.player_name[j] = 0;
    }

    i = 0;
    for (i = 0; i < gamenameToSend.size(); i++) {
      player_info.game_name[i] = gamenameToSend.at(i);
    }
    player_info.game_name[i] = '\0';
    i++;

    for (size_t j = i; j < usernameToSend.size(); j++) {
      player_info.game_name[j] = 0;
    }

    skt.sendall_bytewise(&player_info, sizeof(player_info), &was_closed);
    this->skt_was_closed();
    return this->receive_player_id();
  } catch (const std::exception &err) {
    std::cout
        << "Some error ocurred while trying to send a message to the server."
        << std::endl;
    return ERROR;
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

Snapshot LobbyProtocol::wait_game_start() {
  try {
    Snapshot first_snap;
    skt.recvall_bytewise(&first_snap, sizeof(Snapshot), &was_closed);
    this->skt_was_closed();
    return first_snap;
  } catch (const std::exception &err) {
    throw std::runtime_error(
        "Some error ocurred while trying to receive a message from "
        "the server.");
  }
}

void LobbyProtocol::skt_was_closed() {
  if (was_closed) {
    throw std::runtime_error(
        "The socket was closed and the communication failed.");
  }
}
