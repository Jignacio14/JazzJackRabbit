#ifndef GAME
#define GAME

#include "../common/thread.h"
#include "../data/command_code_dto.h"
#include "../data/snapshot_dto.h"
#include "../engine/base_player.h"
#include "../engine/bullets/bullet.h"
#include "../engine/collectables/base_collectable.h"
#include "../engine/collectables/collectables_handler.h"
#include "../engine/enemies/base_enemy.h"
#include "../engine/enemies/enemies_handler.h"
#include "../engine/global_counter.h"
#include "../engine/jazz.h"
#include "../engine/lori.h"
#include "../engine/spaz.h"
#include "server_game_monitor.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <list>
#include <map>
#include <memory>
#include <sys/types.h>
#include <unordered_map>
#include <utility>

class Game : public Thread {
private:
  GameMonitor &monitor;
  Queue<CommandCodeDto> &messages;
  std::atomic_int32_t players;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, std::unique_ptr<BasePlayer>> players_data;
  // cppcheck-suppress unusedStructMember
  std::vector<std::unique_ptr<BaseEnemy>> enemies;
  // cppcheck-suppress unusedStructMember
  std::vector<Bullet> bullets;
  // cppcheck-suppress unusedStructMember
  std::vector<std::unique_ptr<BaseCollectable>> collectables;
  ServerMap map;
  // cppcheck-suppress unusedStructMember
  Snapshot snapshot;
  // cppcheck-suppress unusedStructMember
  std::atomic_bool gameEnded;
  // cppcheck-suppress unusedStructMember
  int iterationNumber;
  // cppcheck-suppress unusedStructMember
  double rate;
  // cppcheck-suppress unusedStructMember
  CollectablesHandler collectablesHandler;
  // cppcheck-suppress unusedStructMember
  EnemiesHandler enemiesHandler;
  // cppcheck-suppress unusedStructMember
  bool cheat2Activated;

  void gameLoop();
  // cppcheck-suppress unusedPrivateFunction
  void executeAction(const uint8_t &player_id, const uint8_t &action,
                     const uint8_t &data);
  std::unique_ptr<BasePlayer> constructPlayer(uint8_t player_id,
                                              std::string &player_name,
                                              uint8_t player_type);
  double now();
  void rateController(double start, double finish);
  void updateBullets();
  void updateCollectables();
  void handleDrop(uint8_t drop, Rectangle drop_rectangle);
  void updateEnemies();
  void updatePlayers();

public:
  explicit Game(GameMonitor &monitor, Queue<CommandCodeDto> &messages);
  void kill();
  void run() override;
  void addPlayer(const PlayerInfo &player_info, const uint8_t &player_id);
  void ereasePlayer(uint8_t player_id);
  void addPlayerToSnapshot(const PlayerInfo &player_info);
  bool didGameEnd();
  ~Game() override;
};

#endif