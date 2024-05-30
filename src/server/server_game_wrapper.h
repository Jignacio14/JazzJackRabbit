#ifndef GAME_WRAPPER
#define GAME_WRAPPER

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../engine/game.h"
#include "server_game_monitor.h"

#include <string>
#include <sys/types.h>

class GameWrapper {
private:
  // cppcheck-suppress unusedStructMember
  GameMonitor monitor;
  Queue<PlayerStatusDTO> messages;
  // Game game;
  // bool died;

public:
  explicit GameWrapper();
  void registerPlayer(Queue<PlayerStatusDTO> &sender_queue);
  void start();
  const u_int16_t getGamePlayers();
  Queue<PlayerStatusDTO> &getReceiverQueue();
  void ereasedPlayer(Queue<PlayerStatusDTO> game_queue);
  void killGame();
};

#endif