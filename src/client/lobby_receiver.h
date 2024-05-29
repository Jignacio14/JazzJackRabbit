
#ifndef JAZZJACKRABBIT_LOBBY_RECEIVER_H
#define JAZZJACKRABBIT_LOBBY_RECEIVER_H

#include "../common/game_info.h"
#include "../common/socket.h"

class LobbyReceiver {

  Socket &skt;
  // cppcheck-suppress unusedStructMember
  bool &was_closed;

public:
  LobbyReceiver(Socket &socket, bool &was_closed;);

  GameInfoDto get_game_info();
};

#endif // JAZZJACKRABBIT_LOBBY_RECEIVER_H
