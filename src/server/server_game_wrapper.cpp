#include "server_game_wrapper.h"
#include <cstdint>
#include <sys/types.h>
#include <utility>

GameWrapper::GameWrapper() : monitor(), game(monitor, receiver_queue) {}

void GameWrapper::start() {
  this->game.start();
  return;
}

void GameWrapper::killGame() { this->game.kill(); }

std::pair<Queue<std::pair<u_int8_t, u_int8_t>> &, uint8_t>
GameWrapper::addPlayer(Queue<Snapshot> &queue, const PlayerInfo &player_info) {
  const uint8_t player_id = this->monitor.addPlayer(player_info, queue);
  //// TO-DO: Agregar la informacion del jugador al juego
  return std::pair<Queue<std::pair<uint8_t, uint8_t>> &, uint8_t>(
      this->receiver_queue, player_id);
}

void GameWrapper::ereasedPlayer(uint8_t player_id) {
  this->game.ereasePlayer(player_id);
}