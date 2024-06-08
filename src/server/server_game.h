#ifndef GAME
#define GAME

#include "../common/thread.h"
#include "../engine/base_player.h"
#include "../engine/jazz.h"
#include "../engine/lori.h"
#include "../engine/spaz.h"
#include "server_game_monitor.h"
#include <atomic>
#include <cstdint>
#include <list>
#include <map>
#include <unordered_map>
#include <utility>

class Game : public Thread {
private:
  GameMonitor &monitor;
  Queue<std::pair<uint8_t, uint8_t>> &messages;
  std::atomic_int32_t players;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, BasePlayer *> players_data;

  void gameLoop();
  // cppcheck-suppress unusedPrivateFunction
  void executeAction(const uint8_t &player_id, const uint8_t &action);
  BasePlayer *constructPlayer(uint8_t player_id, std::string &player_name);

public:
  explicit Game(GameMonitor &monitor,
                Queue<std::pair<uint8_t, uint8_t>> &messages);
  void kill();
  void run() override;
  void addPlayer(const PlayerInfo &player_info);
  void ereasePlayer(uint8_t player_id);
};

#endif