#ifndef SENDER
#define SENDER

#include "../common/queue.h"
#include "../common/thread.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"

class Sender : public Thread {
private:
  ServerProtocol servprot;
  GamesMonitor &gamesMonitor;

  void sendGamesOptions();
  void setUpPlayerLoop();

public:
  explicit Sender(Socket peer, GamesMonitor &games_monitor_ref);

  void run() override;

  void kill();

  ~Sender() override;
};

#endif