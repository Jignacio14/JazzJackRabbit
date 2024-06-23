
#include "lobby_protocol.h"
#include "../common/jjr2_error.h"
#include "memory.h"
#include <cstdint>

LobbyProtocol::LobbyProtocol(Socket &a_skt) : was_closed(false), skt(a_skt) {}

uint16_t LobbyProtocol::receive_header() {
  uint16_t header = 0;
  this->skt.recvall_bytewise(&header, sizeof(uint16_t), &was_closed);
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
    single_game_info.str_len = ntohs(single_game_info.str_len);
    single_game_info.player_count = ntohs(single_game_info.player_count);
    return single_game_info;
  } catch (const LibError &skt_err) {
    std::string errorMessage =
        "Some error ocurred while trying to receive a message from "
        "the server.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
    // throw std::runtime_error(
    //     "Some error ocurred while trying to receive a message from "
    //     "the server.");
  }
}

uint8_t LobbyProtocol::receive_player_id() {
  try {
    uint8_t player_id = 0;
    skt.recvall_bytewise(&player_id, sizeof(uint8_t), &was_closed);
    this->skt_was_closed();
    return player_id;
  } catch (const LibError &skt_err) {
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

    for (size_t j = i; j < MAX_LEN; j++) {
      player_info.player_name[j] = 0;
    }

    i = 0;
    for (i = 0; i < gamenameToSend.size(); i++) {
      player_info.game_name[i] = gamenameToSend.at(i);
    }
    player_info.game_name[i] = '\0';
    i++;

    for (size_t j = i; j < MAX_LEN; j++) {
      player_info.game_name[j] = 0;
    }

    skt.sendall_bytewise(&player_info, sizeof(player_info), &was_closed);
    this->skt_was_closed();
    return this->receive_player_id();
  } catch (const LibError &skt_err) {
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
  } catch (const LibError &skt_err) {
    std::cout
        << "Some error ocurred while trying to send a message to the server."
        << std::endl;
  }
}

double LobbyProtocol::ntohd(double rawValue) {
  uint64_t networkValue;
  memcpy(&networkValue, &rawValue, sizeof(networkValue));
  networkValue = be64toh(networkValue);
  memcpy(&rawValue, &networkValue, sizeof(rawValue));
  return rawValue;
}

Snapshot LobbyProtocol::deserializeSnapshot(const Snapshot &snapshot) {
  Snapshot finalSnapshot(snapshot);

  finalSnapshot.sizePlayers = ntohs(finalSnapshot.sizePlayers);
  finalSnapshot.sizeEnemies = ntohs(finalSnapshot.sizeEnemies);
  finalSnapshot.sizeCollectables = ntohs(finalSnapshot.sizeCollectables);
  finalSnapshot.sizeBullets = ntohs(finalSnapshot.sizeBullets);

  finalSnapshot.timeLeft = this->ntohd(finalSnapshot.timeLeft);

  for (int i = 0; i < finalSnapshot.sizePlayers; i++) {
    finalSnapshot.players[i].points = ntohl(finalSnapshot.players[i].points);
    finalSnapshot.players[i].life = ntohs(finalSnapshot.players[i].life);
    finalSnapshot.players[i].ammo_gun_1 =
        ntohs(finalSnapshot.players[i].ammo_gun_1);
    finalSnapshot.players[i].ammo_gun_2 =
        ntohs(finalSnapshot.players[i].ammo_gun_2);
    finalSnapshot.players[i].position_x =
        ntohs(finalSnapshot.players[i].position_x);
    finalSnapshot.players[i].position_y =
        ntohs(finalSnapshot.players[i].position_y);
  }

  for (int i = 0; i < finalSnapshot.sizeEnemies; i++) {
    finalSnapshot.enemies[i].entity_id =
        ntohl(finalSnapshot.enemies[i].entity_id);
    finalSnapshot.enemies[i].position_x =
        ntohs(finalSnapshot.enemies[i].position_x);
    finalSnapshot.enemies[i].position_y =
        ntohs(finalSnapshot.enemies[i].position_y);
  }

  for (int i = 0; i < finalSnapshot.sizeBullets; i++) {
    finalSnapshot.bullets[i].entity_id =
        ntohl(finalSnapshot.bullets[i].entity_id);
    finalSnapshot.bullets[i].position_x =
        ntohs(finalSnapshot.bullets[i].position_x);
    finalSnapshot.bullets[i].position_y =
        ntohs(finalSnapshot.bullets[i].position_y);
  }

  for (int i = 0; i < finalSnapshot.sizeCollectables; i++) {
    finalSnapshot.collectables[i].entity_id =
        ntohl(finalSnapshot.collectables[i].entity_id);
    finalSnapshot.collectables[i].position_x =
        ntohs(finalSnapshot.collectables[i].position_x);
    finalSnapshot.collectables[i].position_y =
        ntohs(finalSnapshot.collectables[i].position_y);
  }

  return finalSnapshot;
}

Snapshot LobbyProtocol::wait_game_start(bool &game_started) {
  try {
    Snapshot first_snap;
    skt.recvall_bytewise(&first_snap, sizeof(Snapshot), &was_closed);
    this->skt_was_closed();
    game_started = true;
    return this->deserializeSnapshot(first_snap);
  } catch (const LibError &skt_err) {
    std::string errorMessage =
        "Some error ocurred while trying to receive a message from "
        "the server.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);

    // throw std::runtime_error(
    //     "Some error ocurred while trying to receive a message from "
    //     "the server.");
  }
}

void LobbyProtocol::skt_was_closed() {
  if (was_closed) {
    std::string errorMessage =
        "Some error ocurred while trying to receive a message from "
        "the server.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
    // throw std::runtime_error(
    //     "The socket was closed and the communication failed.");
  }
}
