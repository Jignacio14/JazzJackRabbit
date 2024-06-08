#ifndef SENDER
#define SENDER

#include "../common/queue.h"
#include "../common/snapshot_DTO.h"
#include "../common/thread.h"
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
  Queue<std::pair<uint8_t, uint8_t>> setUpPlayerLoop();
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