#ifndef SENDER
#define SENDER

#include "../common/queue.h"
#include "../common/thread.h"
#include "../data/snapshot_dto.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
#include "server_receiver.h"
#include <cstdint>
#include <utility>

class Sender : public Thread {
private:
  ServerProtocol servprot;
  GamesMonitor &gamesMonitor;
  std::atomic<bool> error;
  Queue<Snapshot> sender_queue;

  void sendGamesOptions();
  Queue<CommandCodeDto> setUpPlayerLoop();
  void runSenderLoop();
  void ValidatePlayerInfo(const PlayerInfo &player_info);

public:
  explicit Sender(Socket peer, GamesMonitor &games_monitor_ref);

  void run() override;

  void kill();

  const bool isAlive();

  ~Sender() override;
};

#endif