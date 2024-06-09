#ifndef GAME_MONITOR
#define GAME_MONITOR

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../data/player_info_dto.h"
#include "../data/snapshot_dto.h"
#include <cstdint>
#include <functional>
#include <list>
#include <mutex>
class GameMonitor {
private:
  // cppcheck-suppress unusedStructMember
  uint8_t players_count;
  // cppcheck-suppress unusedStructMember
  std::list<std::reference_wrapper<Queue<Snapshot>>> queues;
  std::mutex mtx;

public:
  GameMonitor();
  void broadcast(const Snapshot &game_state);
  const uint8_t addPlayer(const PlayerInfo &player_info,
                          Queue<Snapshot> &queue);
  void ereasePlayer(const Queue<Snapshot> &queue);
  ~GameMonitor();
};

#endif