
#ifndef JAZZJACKRABBIT_LOBBY_H
#define JAZZJACKRABBIT_LOBBY_H

#include "../common/socket.h"
#include "lobby_receiver.h"
#include "lobby_sender.h"
#include <atomic>

class Lobby {
private:
  Socket skt;
  // cppcheck-suppress unusedStructMember
  bool was_closed;
  LobbyReceiver receiver;
  LobbySender sender;

public:
  Lobby(const char *hostname, const char *port);

  // Por ahora game info solamente es de 1 game
  GameInfoDto get_games();

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
