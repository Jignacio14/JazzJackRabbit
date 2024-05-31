#ifndef SENDER
#define SENDER

#include "../common/queue.h"
#include "../common/thread.h"
#include "../data/base_dto.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"

class Sender : public Thread {
private:
  ServerProtocol servprot;
  GamesMonitor &gamesMonitor;
  std::atomic<bool> error;

  void sendGamesOptions();
  void setUpPlayerLoop();
  void registerUser();
  void runSenderLoop();

public:
  explicit Sender(Socket peer, GamesMonitor &games_monitor_ref);

  void run() override;

  void kill();

  const bool isAlive();

  ~Sender() override;
};

#endif