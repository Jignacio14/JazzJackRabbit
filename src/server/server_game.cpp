#include "server_game.h"
#include <cstdint>
#include <iostream>
#include <thread>
#include <utility>

#define JAZZ_CODE "J"
#define LORI_CODE "L"
#define SPAZ_CODE "S"

Game::Game(GameMonitor &monitor, Queue<std::pair<uint8_t, uint8_t>> &queue)
    : monitor(monitor), messages(queue), players(0) {}

void Game::gameLoop() {
  while (this->_is_alive) {
    /// Empiezo a calcular la diferencia de tiempo para hacer el sleep
    Snapshot snapshot = Snapshot();
    this->executeAction(1, 1);
    this->monitor.broadcast(snapshot);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

// cppcheck-suppress unusedPrivateFunction
void Game::executeAction(const uint8_t &player_id, const uint8_t &action) {
  std::cout << "Executing action" << std::endl;
}

void Game::run() {
  try {
    this->gameLoop();
  } catch (...) {
    std::cout << "Paso algo en el game loop";
  }
}

BasePlayer *Game::constructPlayer(uint8_t player_id, std::string &player_name) {
  if (player_name == JAZZ_CODE) {
    return new Jazz(player_id, player_name);
  }
  if (player_name == LORI_CODE) {
    return new Lori(player_id, player_name);
  }
  if (player_name == SPAZ_CODE) {
    return new Spaz(player_id, player_name);
  }
  return nullptr;
}

void Game::addPlayer(const PlayerInfo &player_info) {
  this->players++;
  std::string player_name(player_info.player_name);
  BasePlayer *new_player = this->constructPlayer(this->players, player_name);
  if (new_player == nullptr) {
    return;
  }
  this->players_data[this->players] = new_player;
}

void Game::ereasePlayer(uint8_t player_id) {
  // this->monitor.ereasePlayer(this->messages);
  this->players_data.erase(player_id);
  this->players--;
}

void Game::kill() { this->_is_alive = false; }
