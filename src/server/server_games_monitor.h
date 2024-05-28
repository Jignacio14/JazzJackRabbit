#ifndef GAMES_MONITOR
#define GAMES_MONITOR

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
  std::unordered_map<std::string, GameWrapper> game_tracker;

  void createNewGame();
  void registerUser();

public:
  explicit GamesMonitor();

  void registerUser(const std::string &server_name,
                    const Queue<std::string> &queue);

  const std::unordered_map<std::string, uint16_t> getGamesStatus();
  // void registerGame(const std::string& server_name);

  void ereasePlayer(const std::string &server_name, Queue<std::string>);
  void ereaseGame(const std::string &server_name);

  ~GamesMonitor();
};

#endif