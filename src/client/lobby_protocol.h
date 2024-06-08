
#ifndef JAZZJACKRABBIT_LOBBY_PROTOCOL_H
#define JAZZJACKRABBIT_LOBBY_PROTOCOL_H

#include "../common/game_info.h"
#include "../common/snapshot_DTO.h"
#include "../common/socket.h"
#include "../data/player_info_dto.h"
#include <atomic>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <vector>

#define REFRESH 1
#define NEW_GAME 2
#define ERROR -1
#define GAME_START 1

class LobbyProtocol {
private:
  // cppcheck-suppress unusedStructMember
  bool was_closed;
  Socket &skt;

public:
  explicit LobbyProtocol(Socket &a_skt);

  /*
   * Receives the number of total games that the server has, and returns that
   * number.
   * */
  uint16_t receive_header();

  /*
   * Receives a single game info and returns it.
   * */
  GameInfoDto receive_game();

  /*
   * Sends the server a signal to refresh the games.
   * */
  void send_refresh();

  /*
   * Receives the player id from the server and returns it.
   */
  uint8_t receive_player_id();

  /*
   * Sends the game de player selected to the server. This includes game option,
   * gamename, the gamename. Then, it sends the character chosen by the player,
   * and the username. Finally, it returns the player id.
   * */
  uint8_t send_selected_game(const std::vector<char> &gamename,
                             char user_character,
                             const std::vector<char> &username);

  /*
   *
   * */
  Snapshot wait_game_start();

  /*
   * Throws an error if the socket was closed during a communication.
   * */
  void skt_was_closed();
};

#endif // JAZZJACKRABBIT_LOBBY_PROTOCOL_H
