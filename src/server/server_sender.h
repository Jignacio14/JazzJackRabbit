#ifndef SENDER
#define SENDER

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "../data/communication_dto.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"

class Sender : public Thread {
private:
  ServerProtocol servprot;
  GamesMonitor &gamesMonitor;
  Queue<BaseDTO *> queue;

  void sendGameInfo();
  void runSenderLoop();

public:
  explicit Sender(Socket peer, GamesMonitor &games_monitor_ref);

  void run() override;

  void kill();

  ~Sender() override;
};

#endif