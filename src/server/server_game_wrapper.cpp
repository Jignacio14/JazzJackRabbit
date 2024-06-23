#include "server_game_wrapper.h"
#include <mutex>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

GameWrapper::GameWrapper()
    : monitor(), game(monitor, std::ref(this->receiver_queue)), players(0) {}

void GameWrapper::start() {
  std::lock_guard<std::mutex> lck(this->mtx);
  this->game.start();
}

const u_int16_t GameWrapper::getGamePlayers() {
  std::lock_guard<std::mutex> lck(this->mtx);
  return this->players;
}

void GameWrapper::killGame() {
  if (this->game.is_alive()) {
    this->game.kill();
    this->game.join();
  }
}

std::pair<Queue<CommandCodeDto> &, uint8_t>
GameWrapper::addPlayer(Queue<Snapshot> &queue, const PlayerInfo &player_info) {

  std::lock_guard<std::mutex> lck(this->mtx);
  const uint8_t player_id = this->monitor.addPlayer(player_info, queue);
  this->players++;

  this->game.addPlayer(player_info, player_id);

  if (globalConfigs.getMaxPlayersPerGame() == this->players) {
    this->game.start();
  }

  return std::pair<Queue<CommandCodeDto> &, uint8_t>(this->receiver_queue,
                                                     player_id);
}

bool GameWrapper::isGameRunning() {

  std::lock_guard<std::mutex> lck(this->mtx);
  return !this->game.didGameEnd();
}

void GameWrapper::ereasedPlayer(const uint8_t &player_id,
                                const Queue<Snapshot> &sender_queue) {
  std::lock_guard<std::mutex> lck(this->mtx);
  this->monitor.ereasePlayer(sender_queue);
  this->players--;
  this->game.ereasePlayer(player_id);
}