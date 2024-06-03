#include "server_game_wrapper.h"
#include <cstdint>

GameWrapper::GameWrapper() : monitor() {}

void GameWrapper::start() {
  // monitor.start();
  return;
}

const u_int16_t GameWrapper::getGamePlayers() { return 2; }

void GameWrapper::killGame() {
  // monitor.stop();
}

std::pair<Queue<BaseDTO *> &, uint8_t>
GameWrapper::addPlayer(Queue<BaseDTO *> &queue, PlayerInfo &player_info) {
  const uint8_t player_id = this->monitor.addPlayer(player_info, queue);
  //// TO-DO: Agregar la informacion del jugador al juego
  return std::pair<Queue<BaseDTO *> &, uint8_t>(this->receiver_queue,
                                                player_id);
}
