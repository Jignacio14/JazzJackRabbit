#include "server_games_monitor.h"
#include "server_game_wrapper.h"
#include <string>

GamesMonitor::GamesMonitor() {}

void GamesMonitor::registerUser(const std::string &server_name,
                                const Queue<PlayerStatusDTO> &snd_queue) {
  std::lock_guard<std::mutex> lock(mtx);
  auto it = this->game_tracker.find(server_name);
  if (it != this->game_tracker.end()) {
    this->registerPlayer(it->second, snd_queue);
  } else {
    this->startNewGame(snd_queue);
  }
}

const std::unordered_map<std::string, uint16_t> GamesMonitor::getGamesStatus() {
  std::lock_guard<std::mutex> lock(mtx);
  std::unordered_map<std::string, uint16_t> games_data;
  for (auto &game : game_tracker) {
    games_data[game.second.getGameName()] = game.second.getGamePlayers();
  }
  return games_data;
}

// cppcheck-suppress constParameterReference
void GamesMonitor::registerPlayer(GameWrapper &game,
                                  const Queue<PlayerStatusDTO> &queue) {}

void GamesMonitor::startNewGame(const Queue<PlayerStatusDTO> &queue) {}