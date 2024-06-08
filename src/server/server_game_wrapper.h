#ifndef GAME_WRAPPER
#define GAME_WRAPPER

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../data/player_info_dto.h"
#include "server_game.h"
#include "server_game_monitor.h"

#include "../common/global_configs.h"
#include "server_game.h"
#include <atomic>
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <utility>

class GameWrapper {
private:
  GameMonitor monitor;
  Queue<std::pair<u_int8_t, u_int8_t>> receiver_queue;
  Game game;
  std::atomic_int8_t players;

public:
  explicit GameWrapper();
  void start();
  const u_int16_t getGamePlayers();
  void killGame();
  void ereasedPlayer(uint8_t player_id);
  std::pair<Queue<std::pair<uint8_t, uint8_t>> &, uint8_t>
  addPlayer(Queue<Snapshot> &queue, const PlayerInfo &player_info);
};

#endif