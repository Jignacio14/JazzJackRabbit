#ifndef GAME
#define GAME

#include "../common/thread.h"
#include "server_game_monitor.h"
#include <atomic>
#include <list>
#include <map>

class Game : public Thread {
private:
  GameMonitor &monitor;
  Queue<BaseDTO *> &messages;
  std::atomic_int32_t players;
  void gameLoop();
  void waitingRoomLoop();
  void executeAction(BaseDTO *dto);

public:
  explicit Game(GameMonitor &monitor, Queue<BaseDTO *> &messages);
  void kill();
  void run() override;
  void addPlayer(const PlayerInfo &player_info);
};

#endif