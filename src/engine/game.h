#ifndef GAME_H
#define GAME_H

#include "../common/thread.h"
#include "../server/server_game_monitor.h"

class Game : public Thread {
private:
  Queue<PlayerStatusDTO> &messages;
  GameMonitor monitor;

public:
  explicit Game(Queue<PlayerStatusDTO> &messages);
  // void run();
};

#endif