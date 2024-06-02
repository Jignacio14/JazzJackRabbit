#include "./server_games_monitor.h"
#include <mutex>
#include <string>
#include <sys/types.h>
#include <unordered_map>

GamesMonitor::GamesMonitor() {}

std::unordered_map<std::string, uint16_t> GamesMonitor::getGamesStartInfo() {
  std::lock_guard<std::mutex> lck(this->mtx);
  std::unordered_map<std::string, uint16_t> games_info;
  for (const auto &game : game_tracker) {
    games_info[game.first] = game.second->getGamePlayers();
  }
  return games_info;
}

GamesMonitor::~GamesMonitor() {
  for (const auto &game : game_tracker) {
    delete game.second;
  }
}
