#include "server_game_wrapper.h"
#include <cstdint>

GameWrapper::GameWrapper() : monitor() {}

void GameWrapper::start() {
  // monitor.start();
  // game.start();
  return;
}

const u_int16_t GameWrapper::getGamePlayers() { return players_count; }

void GameWrapper::killGame() {
  // monitor.stop();
  // game.stop();
}

std::pair<Queue<BaseDTO *> &, uint8_t>
GameWrapper::addPlayer(Queue<BaseDTO *> &queue, PlayerInfo &player_info) {
  const uint8_t player_id = this->monitor.addPlayer(player_info, queue);
  //// TO-DO: Agregar la informacion del jugador al juego
  players_count++;
  return std::pair<Queue<BaseDTO *> &, uint8_t>(this->receiver_queue,
                                                player_id);
}
