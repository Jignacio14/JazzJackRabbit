#ifndef GAMES_MONITOR
#define GAMES_MONITOR

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "server_game_wrapper.h"
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>

class GamesMonitor {
private:
  std::mutex mtx;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, GameWrapper *> game_tracker;

  void registerPlayer(GameWrapper &game, Queue<PlayerStatusDTO> &queue);
  void startNewGame(const std::string &server_name,
                    Queue<PlayerStatusDTO> &queue);

public:
  explicit GamesMonitor();

  void registerUser(const std::string &server_name,
                    Queue<PlayerStatusDTO> &queue);

  const std::unordered_map<std::string, uint16_t> getGamesStatus();
  // void registerGame(const std::string& server_name);

  Queue<PlayerStatusDTO> &getReceiverQueue(const std::string &server_name);
  void ereasePlayer(const std::string &server_name,
                    Queue<PlayerStatusDTO> game_queue);
  void ereaseGame(const std::string &server_name);

  ~GamesMonitor();
};

#endif