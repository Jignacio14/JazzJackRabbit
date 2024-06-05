
#ifndef JAZZJACKRABBIT_LOBBY_H
#define JAZZJACKRABBIT_LOBBY_H

#include "lobby_protocol.h"
#include <cstdint>

class Lobby {
private:
  Socket skt;
  LobbyProtocol protocol;
  // cppcheck-suppress unusedStructMember
  uint8_t player_id;
  // cppcheck-suppress unusedStructMember
  bool skt_ownership;

public:
  Lobby(const char *hostname, const char *port);

  /*
   * Returns all the games received from the server.
   * */
  std::vector<GameInfoDto> get_games();

  /*
   * Sends a message to the server to refresh the games, and then returns the
   * refreshed games.
   * */
  std::vector<GameInfoDto> refresh_games();

  /*
   * Sends the game match that the player chose, and the character selected by
   * the player and the username.
   * */
  void send_selected_game(const std::string &gamename, char user_character,
                          const std::string &username);

  /*
   * Returns the player id.
   */
  uint8_t get_player_id();

  /*
   * Moves socket ownership with move semantics.
   * */
  Socket transfer_socket();

  /*
   *
   * */
  bool wait_game_start();

  /*
   * Close and shutdown the socket.
   * */
  void quit_game();

  /*
   * Close and shutdown the socket, if the socket is owned by the lobby.
   */
  ~Lobby();
};

#endif // JAZZJACKRABBIT_LOBBY_H
