#ifndef GAMES_MONITOR
#define GAMES_MONITOR

// #include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../data/base_dto.h"
#include "../data/player_info_dto.h"
#include "./server_game_wrapper.h"
#include <cstdint>
#include <mutex>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <utility>

class GamesMonitor {
private:
  std::mutex mtx;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, GameWrapper *> game_tracker;

  std::pair<Queue<BaseDTO *> &, u_int8_t>
  registerToExistingGame(PlayerInfo &player_status,
                         Queue<BaseDTO *> &sender_queue);
  std::pair<Queue<BaseDTO *> &, u_int8_t>
  createNewGame(PlayerInfo &player_status, Queue<BaseDTO *> &sender_queue);
  std::string getGameName(PlayerInfo &player_status);

public:
  explicit GamesMonitor();

  std::unordered_map<std::string, uint16_t> getGamesStartInfo();
  std::pair<Queue<BaseDTO *> &, u_int8_t>
  registerPlayer(PlayerInfo &player_status, Queue<BaseDTO *> &sender_queue);

  ~GamesMonitor();
};

#endif