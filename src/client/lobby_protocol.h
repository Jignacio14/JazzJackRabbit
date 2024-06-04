
#ifndef JAZZJACKRABBIT_LOBBY_PROTOCOL_H
#define JAZZJACKRABBIT_LOBBY_PROTOCOL_H

#include "../common/game_info.h"
#include "../common/socket.h"
#include <atomic>
#include <iostream>
#include <netinet/in.h>
#include <vector>

#define REFRESH 1

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
   * Sends the game de player selected to the server. First, game option, then
   * length of gamename and then the gamename. Then, it sends the character
   * chosen by the player, and then the username.
   * */
  void send_selected_game(const std::vector<char> &gamename,
                          uint8_t game_option, char user_character,
                          const std::vector<char> &username);

  /*
   * Waits for the server to send the confirmation message. Returns true if this
   * happens, false if not.
   * */
  bool wait_game_start();

  /*
   * Throws an error if the socket was closed during a communication.
   * */
  void skt_was_closed();
};

#endif // JAZZJACKRABBIT_LOBBY_PROTOCOL_H
