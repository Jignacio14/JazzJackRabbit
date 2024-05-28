#include "server_games_monitor.h"
#include "server_game_wrapper.h"
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>

GamesMonitor::GamesMonitor() {}

void GamesMonitor::registerUser(const std::string &server_name,
                                const Queue<std::string> &queue) {
  std::lock_guard<std::mutex> lock(mtx);
  auto it = this->game_tracker.find(server_name);
  GameWrapper game;
  if (it != this->game_tracker.end()) {
    game = it->second;
  } else {
    GameWrapper new_game;
    this->game_tracker[server_name] = new_game;
    new_game.start();
    game = new_game;
  }

  game.registerPlayer();
}

const std::unordered_map<std::string, uint16_t> GamesMonitor::getGamesStatus() {
  std::lock_guard<std::mutex> lock(mtx);
  std::unordered_map<std::string, uint16_t> games_data;
  for (auto game : game_tracker) {
    games_data[game.second.getGameName()] = game.second.getGamePlayers();
  }
  return games_data;
}