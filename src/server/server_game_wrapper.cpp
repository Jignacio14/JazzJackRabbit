#include "server_game_wrapper.h"

GameWrapper::GameWrapper() : monitor() {}

void GameWrapper::registerPlayer(Queue<PlayerStatusDTO> &sender_queue) {
  monitor.addPlayer(sender_queue);
}

Queue<PlayerStatusDTO> &GameWrapper::getReceiverQueue() {
  return this->messages;
}

void GameWrapper::ereasedPlayer(const Queue<PlayerStatusDTO> &game_queue) {
  // monitor.removePlayer(game_queue);
  return;
}

void GameWrapper::start() {
  // monitor.start();
  return;
}

const u_int16_t GameWrapper::getGamePlayers() { return 2; }

void GameWrapper::killGame() {
  // monitor.stop();
}
