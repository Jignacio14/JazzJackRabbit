#ifndef GAME_WRAPPER
#define GAME_WRAPPER

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "server_game_monitor.h"
#include <string>
#include <sys/types.h>

class GameWrapper {
private:
  // cppcheck-suppress unusedStructMember
  std::string game_name;
  GameMonitor monitor;

public:
  void registerPlayer();
  void start();
  const std::string getGameName();
  const u_int16_t getGamePlayers();
  void ereasedPlayer(Queue<PlayerStatusDTO> game_queue);
  void killGame();
};

#endif