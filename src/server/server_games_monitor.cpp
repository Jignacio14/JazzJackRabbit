#include "server_games_monitor.h"
#include "server_game_wrapper.h"
#include <string>

GamesMonitor::GamesMonitor() {}

void GamesMonitor::registerUser(const std::string &server_name,
                                Queue<PlayerStatusDTO> &snd_queue) {
  std::lock_guard<std::mutex> lock(mtx);
  auto it = this->game_tracker.find(server_name);
  if (it == nullptr) {
    this->startNewGame(server_name, snd_queue);
    return;
  }
  this->registerPlayer(*it->second, snd_queue);
}

const std::unordered_map<std::string, uint16_t> GamesMonitor::getGamesStatus() {
  std::lock_guard<std::mutex> lock(mtx);
  std::unordered_map<std::string, uint16_t> games_data;
  for (const auto &game : game_tracker) {
    games_data[game.first] = game.second->getGamePlayers();
  }
  return games_data;
}

void GamesMonitor::registerPlayer(GameWrapper &game,
                                  Queue<PlayerStatusDTO> &queue) {
  game.registerPlayer(queue);
}

void GamesMonitor::startNewGame(const std::string &server_name,
                                Queue<PlayerStatusDTO> &queue) {
  GameWrapper *new_game = new GameWrapper();
  new_game->start();
  this->game_tracker[server_name] = new_game;
  this->registerPlayer(*new_game, queue);
}

Queue<PlayerStatusDTO> &
GamesMonitor::getReceiverQueue(const std::string &server_name) {
  std::lock_guard<std::mutex> lock(mtx);
  return this->game_tracker[server_name]->getReceiverQueue();
}

GamesMonitor::~GamesMonitor() {
  for (const auto &game : game_tracker) {
    delete game.second;
  }
}