#ifndef GAME_WRAPPER
#define GAME_WRAPPER

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../data/base_dto.h"
#include "../data/player_info_dto.h"
#include "server_game.h"
#include "server_game_monitor.h"

#include "server_game.h"
#include <atomic>
#include <cstdint>
#include <string>
#include <sys/types.h>

class GameWrapper {
private:
  GameMonitor monitor;
  Queue<BaseDTO *> receiver_queue;
  std::atomic_uint16_t players_count;
  Game game;

public:
  explicit GameWrapper();
  void start();
  const u_int16_t getGamePlayers();
  void killGame();
  void ereasedPlayer(uint8_t player_id);
  std::pair<Queue<BaseDTO *> &, uint8_t> addPlayer(Queue<BaseDTO *> &queue,
                                                   PlayerInfo &player_info);
};

#endif