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

std::pair<Queue<CommandCodeDto> &, uint8_t>
GamesMonitor::registerPlayer(PlayerInfo &player_status,
                             Queue<Snapshot> &sender_queue) {
  std::lock_guard<std::mutex> lck(this->mtx);

  std::string server_name(player_status.game_name);
  if (game_tracker.find(server_name) == game_tracker.end()) {
    /// El juego no existe por lo tanto debo crear uno
    // return
    // cppcheck-suppress missingReturn
    return this->createNewGame(player_status, sender_queue);
  }
  /// EL juego existe, solo debo agregar al jugador
  return this->registerToExistingGame(player_status, sender_queue);
}

std::string GamesMonitor::getGameName(PlayerInfo &player_status) {
  return std::string(player_status.game_name);
}

std::pair<Queue<CommandCodeDto> &, uint8_t>
GamesMonitor::registerToExistingGame(PlayerInfo &player_status,
                                     Queue<Snapshot> &sender_queue) {
  std::string server_name = this->getGameName(player_status);
  return game_tracker[server_name]->addPlayer(sender_queue, player_status);
}

std::pair<Queue<CommandCodeDto> &, uint8_t>
GamesMonitor::createNewGame(PlayerInfo &player_status,
                            Queue<Snapshot> &sender_queue) {
  std::unique_ptr<GameWrapper> game = std::make_unique<GameWrapper>();
  std::string server_name = this->getGameName(player_status);
  game_tracker[server_name] = std::move(game);
  return game_tracker[server_name]->addPlayer(sender_queue, player_status);
}

void GamesMonitor::removeEndedGames() {
  std::lock_guard<std::mutex> lck(this->mtx);

  for (auto it = game_tracker.begin(); it != game_tracker.end();) {
    if (!it->second->isGameRunning()) {
      it = game_tracker.erase(it);
    } else {
      ++it;
    }
  }
}

void GamesMonitor::removePlayer(const std::string &game_name,
                                const uint8_t &player_id,
                                Queue<Snapshot> &sender_queue) {

  std::lock_guard<std::mutex> lck(this->mtx);
  if (game_tracker.find(game_name) == game_tracker.end()) {
    return;
  }
  this->game_tracker[game_name]->ereasedPlayer(player_id, sender_queue);
}

GamesMonitor::~GamesMonitor() {}
