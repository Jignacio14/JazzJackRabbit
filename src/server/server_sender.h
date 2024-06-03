#ifndef SENDER
#define SENDER

#include "../common/queue.h"
#include "../common/thread.h"
#include "../data/base_dto.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
#include "server_receiver.h"

class Sender : public Thread {
private:
  ServerProtocol servprot;
  GamesMonitor &gamesMonitor;
  std::atomic<bool> error;
  Queue<BaseDTO *> sender_queue;

  void sendGamesOptions();
  Queue<BaseDTO *> &setUpPlayerLoop();
  void registerUser(Queue<BaseDTO *> &receiver_queue);
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