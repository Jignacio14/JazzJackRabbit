
#ifndef JAZZJACKRABBIT_LOBBY_H
#define JAZZJACKRABBIT_LOBBY_H

#include "..common/socket.h"
#include <atomic>

class Lobby {
private:
  Socket skt;
  std::atomic<bool> alive;
  LobbyReceiver receiver;
  LobbySender sender;

public:
  Lobby(const char *hostname, const char *port);

  // Por ahora game info solamente es de 1 game
  GameInfoDto get_games();
};

#endif // JAZZJACKRABBIT_LOBBY_H
