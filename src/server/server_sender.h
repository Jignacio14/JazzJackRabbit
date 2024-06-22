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
  Queue<Snapshot> sender_queue;
  // cppcheck-suppress unusedStructMember
  std::string game_name;
  // cppcheck-suppress unusedStructMember
  uint8_t player_id;

  void sendGamesOptions();
  Queue<CommandCodeDto> &setUpPlayerLoop();
  void runSenderLoop();
  void ValidatePlayerInfo(const PlayerInfo &player_info);
  void savePlayerInfo(const PlayerInfo &player_info, const uint8_t &player_id);
  void logOutPlayer();

public:
  Sender(Socket peer, GamesMonitor &games_monitor_ref);

  virtual void run() override;

  void kill();

  const bool isAlive();

  ~Sender() override;
};

#endif