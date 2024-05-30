
#ifndef JAZZJACKRABBIT_LOBBY_PROTOCOL_H
#define JAZZJACKRABBIT_LOBBY_PROTOCOL_H

#include "../common/game_info.h"
#include "../common/socket.h"
#include <atomic>
#include <iostream>
#include <vector>

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
  uint8_t receive_header();

  /*
   * Receives a single game info and returns it.
   * */
  GameInfoDto receive_game();

  /*
   * Sends the game de player selected to the server.
   * */
  void send_selected_game(const std::vector<char> &gamename);

  /*
   *
   * */
  bool wait_confirmation();
};

#endif // JAZZJACKRABBIT_LOBBY_PROTOCOL_H
