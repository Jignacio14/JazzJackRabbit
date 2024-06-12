#ifndef GAME
#define GAME

#include "../common/thread.h"
#include "../data/command_code_dto.h"
#include "../data/snapshot_dto.h"
#include "../engine/base_player.h"
#include "../engine/jazz.h"
#include "../engine/lori.h"
#include "../engine/spaz.h"
#include "server_game_monitor.h"
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <list>
#include <map>
#include <unordered_map>
#include <utility>

class Game : public Thread {
private:
  GameMonitor &monitor;
  Queue<CommandCodeDto> &messages;
  std::atomic_int32_t players;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, BasePlayer *> players_data;
  // cppcheck-suppress unusedStructMember
  Snapshot snapshot;
  // cppcheck-suppress unusedStructMember
  int iterationNumber;
  // cppcheck-suppress unusedStructMember
  double rate;

  void gameLoop();
  // cppcheck-suppress unusedPrivateFunction
  void executeAction(const uint8_t &player_id, const uint8_t &action,
                     const uint8_t &data);
  BasePlayer *constructPlayer(uint8_t player_id, std::string &player_name,
                              uint8_t player_type);
  double now();
  void rateController(double start, double finish);

public:
  explicit Game(GameMonitor &monitor, Queue<CommandCodeDto> &messages);
  void kill();
  void run() override;
  void addPlayer(const PlayerInfo &player_info, const uint8_t &player_id);
  void ereasePlayer(uint8_t player_id);
  void addPlayerToSnapshot(const PlayerInfo &player_info);
};

#endif