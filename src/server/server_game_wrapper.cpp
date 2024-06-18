#include "server_game_wrapper.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

GameWrapper::GameWrapper()
    : monitor(), game(monitor, std::ref(this->receiver_queue)) {}

void GameWrapper::start() { this->game.start(); }

const u_int16_t GameWrapper::getGamePlayers() { return this->players; }

void GameWrapper::killGame() { this->game.kill(); }

std::pair<Queue<CommandCodeDto> &, uint8_t>
GameWrapper::addPlayer(Queue<Snapshot> &queue, const PlayerInfo &player_info) {

  const uint8_t player_id = this->monitor.addPlayer(player_info, queue);
  this->players++;

  this->game.addPlayer(player_info, player_id);

  if (globalConfigs.getMaxPlayersPerGame() == this->players) {
    this->game.start();
  }

  return std::pair<Queue<CommandCodeDto> &, uint8_t>(this->receiver_queue,
                                                     player_id);
}

bool GameWrapper::isGameRunning() { return this->game.is_alive(); }

void GameWrapper::ereasedPlayer(uint8_t player_id) {
  // this->monitor.ereasePlayer();
  this->players--;
  this->game.ereasePlayer(player_id);
}