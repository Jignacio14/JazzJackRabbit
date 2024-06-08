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

std::pair<Queue<Snapshot> &, uint8_t>
GamesMonitor::registerPlayer(PlayerInfo &player_status,
                             Queue<Snapshot> &sender_queue) {
  std::lock_guard<std::mutex> lck(this->mtx);
  std::string server_name(player_status.game_name.begin(),
                          player_status.game_name.end());
  if (game_tracker.find(server_name) != game_tracker.end()) {
    // game_tracker[server_name] = new GameWrapper(server_name);
    /// El juego no existe por lo tanto debo crear uno
    // return
    // cppcheck-suppress missingReturn
    return this->createNewGame(player_status, sender_queue);
  }
  /// EL juego existe, solo debo agregar al jugador
  return this->registerToExistingGame(player_status, sender_queue);
}

std::string GamesMonitor::getGameName(PlayerInfo &player_status) {
  return std::string(player_status.game_name.begin(),
                     player_status.game_name.end());
}

std::pair<Queue<Snapshot> &, uint8_t>
GamesMonitor::registerToExistingGame(PlayerInfo &player_status,
                                     Queue<Snapshot> &sender_queue) {
  std::lock_guard<std::mutex> lck(this->mtx);
  std::string server_name = this->getGameName(player_status);
  return game_tracker[server_name]->addPlayer(sender_queue, player_status);
}

std::pair<Queue<Snapshot> &, uint8_t>
GamesMonitor::createNewGame(PlayerInfo &player_status,
                            Queue<Snapshot> &sender_queue) {
  std::lock_guard<std::mutex> lck(this->mtx);
  GameWrapper *game = new GameWrapper();
  std::string server_name = this->getGameName(player_status);
  game_tracker[server_name] = game;
  return game->addPlayer(sender_queue, player_status);
}

GamesMonitor::~GamesMonitor() {
  for (const auto &game : game_tracker) {
    delete game.second;
  }
}
