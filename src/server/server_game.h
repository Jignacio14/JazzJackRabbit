#ifndef GAME
#define GAME

#include "../common/thread.h"
#include "server_game_monitor.h"
#include <list>
#include <map>

class Game : public Thread {
private:
  GameMonitor &monitor;

public:
  explicit Game(GameMonitor &monitor);
  void kill();
};

#endif