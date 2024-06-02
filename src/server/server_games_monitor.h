#ifndef GAMES_MONITOR
#define GAMES_MONITOR

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../data/base_dto.h"
#include "./server_game_wrapper.h"
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>

class GamesMonitor {
private:
  std::mutex mtx;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, GameWrapper *> game_tracker;

public:
  explicit GamesMonitor();

  std::unordered_map<std::string, uint16_t> getGamesStartInfo();

  ~GamesMonitor();
};

#endif