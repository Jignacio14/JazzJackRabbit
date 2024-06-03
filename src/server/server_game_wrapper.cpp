#include "server_game_wrapper.h"

GameWrapper::GameWrapper() : monitor() {}

void GameWrapper::start() {
  // monitor.start();
  return;
}

const u_int16_t GameWrapper::getGamePlayers() { return 2; }

void GameWrapper::killGame() {
  // monitor.stop();
}
