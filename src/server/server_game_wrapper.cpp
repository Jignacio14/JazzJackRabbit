#include "server_game_wrapper.h"

GameWrapper::GameWrapper() : monitor(), game(monitor, receiver_queue) {}

void GameWrapper::start() {
  this->game.start();
  return;
}

const u_int16_t GameWrapper::getGamePlayers() { return players_count; }

void GameWrapper::killGame() { this->game.kill(); }

std::pair<Queue<BaseDTO *> &, uint8_t>
GameWrapper::addPlayer(Queue<BaseDTO *> &queue, PlayerInfo &player_info) {
  const uint8_t player_id = this->monitor.addPlayer(player_info, queue);
  //// TO-DO: Agregar la informacion del jugador al juego
  players_count++;
  return std::pair<Queue<BaseDTO *> &, uint8_t>(this->receiver_queue,
                                                player_id);
}

void GameWrapper::ereasedPlayer(uint8_t player_id) {
  this->game.ereasePlayer(player_id);
  players_count--;
}