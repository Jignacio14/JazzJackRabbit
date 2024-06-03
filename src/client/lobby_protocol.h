
#ifndef JAZZJACKRABBIT_LOBBY_PROTOCOL_H
#define JAZZJACKRABBIT_LOBBY_PROTOCOL_H

#include "../common/game_info.h"
#include "../common/socket.h"
#include <atomic>
#include <iostream>
#include <netinet/in.h>
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
  uint16_t receive_header();

  /*
   * Receives a single game info and returns it.
   * */
  GameInfoDto receive_game();

  /*
   * Sends the game de player selected to the server. First, game option, then
   * length of gamename and then the gamename. Then, it sends the character
   * chosen by the player, and then the username.
   * */
  void send_selected_game(const std::vector<char> &gamename,
                          uint8_t game_option, char user_character,
                          const std::vector<char> &username);

  /*
   *
   * */
  bool wait_game_start();
};

#endif // JAZZJACKRABBIT_LOBBY_PROTOCOL_H
