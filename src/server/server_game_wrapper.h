#ifndef GAME_WRAPPER
#define GAME_WRAPPER

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../data/base_dto.h"
#include "../data/player_info_dto.h"
#include "../engine/game.h"
#include "server_game_monitor.h"

#include <atomic>
#include <string>
#include <sys/types.h>

class GameWrapper {
private:
  GameMonitor monitor;
  Queue<BaseDTO *> receiver_queue;
  std::atomic_uint16_t players_count;

public:
  explicit GameWrapper();
  void start();
  const u_int16_t getGamePlayers();
  void killGame();

  std::pair<Queue<BaseDTO *> &, uint8_t> addPlayer(Queue<BaseDTO *> &queue,
                                                   PlayerInfo &player_info);
};

#endif