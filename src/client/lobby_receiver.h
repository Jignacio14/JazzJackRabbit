
#ifndef JAZZJACKRABBIT_LOBBY_RECEIVER_H
#define JAZZJACKRABBIT_LOBBY_RECEIVER_H

#include "../common/game_info.h"
#include "../common/socket.h"

class LobbyReceiver {

  Socket &skt;

public:
  LobbyReceiver();

  GameInfoDto get_game_info();
};

#endif // JAZZJACKRABBIT_LOBBY_RECEIVER_H
