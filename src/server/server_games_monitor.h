#ifndef GAMES_MONITOR
#define GAMES_MONITOR

#include "../common/queue.h"
#include "../data/player_info_dto.h"
#include "../data/snapshot_dto.h"
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
  std::unordered_map<std::string, std::unique_ptr<GameWrapper>> game_tracker;

  std::pair<Queue<CommandCodeDto> &, u_int8_t>
  registerToExistingGame(PlayerInfo &player_status,
                         Queue<Snapshot> &sender_queue);

  std::pair<Queue<CommandCodeDto> &, u_int8_t>
  createNewGame(PlayerInfo &player_status, Queue<Snapshot> &sender_queue);

  std::string getGameName(PlayerInfo &player_status);

public:
  explicit GamesMonitor();

  std::unordered_map<std::string, uint16_t> getGamesStartInfo();
  std::pair<Queue<CommandCodeDto> &, u_int8_t>
  registerPlayer(PlayerInfo &player_status, Queue<Snapshot> &sender_queue);
  void removeEndedGames();
  void removePlayer(const std::string &game_name, const u_int8_t &player_id,
                    Queue<Snapshot> &sender_queue);
  void killAll();

  ~GamesMonitor();
};

#endif