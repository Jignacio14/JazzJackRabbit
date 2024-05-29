#ifndef GAME_MONITOR
#define GAME_MONITOR

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include <cstdint>
#include <functional>
#include <list>
#include <mutex>
class GameMonitor {
private:
  // cppcheck-suppress unusedStructMember
  uint16_t players_count;
  // cppcheck-suppress unusedStructMember
  std::list<std::reference_wrapper<Queue<PlayerStatusDTO>>> queues;
  std::mutex mtx;

public:
  GameMonitor();
  void broadcast(const PlayerStatusDTO &msj);
  void addPlayer(Queue<PlayerStatusDTO> &queue);
  void ereasePlayer(const Queue<PlayerStatusDTO> &queue);
  ~GameMonitor();
};

#endif