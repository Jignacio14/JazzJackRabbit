
#ifndef JAZZJACKRABBIT_LOBBY_H
#define JAZZJACKRABBIT_LOBBY_H

#include "lobby_protocol.h"

class Lobby {
private:
  Socket skt;
  LobbyProtocol protocol;

public:
  Lobby(const char *hostname, const char *port);

  /*
   * Returns all the games received from the server.
   * */
  std::vector<GameInfoDto> get_games();

  /*
   * Sends the game match that the player chose.
   * */
  void send_selected_game(const std::vector<char> &gamename);

  /*
   * Moves socket ownership with move semantics.
   * */
  Socket transfer_socket();
};

#endif // JAZZJACKRABBIT_LOBBY_H
