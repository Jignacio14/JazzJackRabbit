#include "server_game.h"
#include <cstdint>
#include <iostream>
#include <thread>
#include <utility>
#define MIN_PLAYERS 2

Game::Game(GameMonitor &monitor, Queue<std::pair<uint8_t, uint8_t>> &queue)
    : monitor(monitor), messages(queue), players(0) {}

void Game::waitingRoomLoop() {
  while (this->players < MIN_PLAYERS) {
  }
}

void Game::gameLoop() {
  while (this->_is_alive) {
    /// Empiezo a calcular la diferencia de tiempo para hacer el sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

// cppcheck-suppress unusedPrivateFunction
void Game::executeAction(const uint8_t &player_id, const uint8_t &action) {
  std::cout << "Executing action" << std::endl;
}

void Game::run() {
  this->waitingRoomLoop();
  this->gameLoop();
}

BasePlayer *Game::constructPlayer(uint8_t player_id, std::string &player_name) {
  using PlayerFactory = std::function<BasePlayer *(uint8_t, std::string &)>;
  static const std::unordered_map<uint8_t, PlayerFactory> factories = {
      {1, [](uint8_t id, std::string &name) { return new Jazz(id, name); }},
      {2, [](uint8_t id, std::string &name) { return new Lori(id, name); }},
      {3, [](uint8_t id, std::string &name) { return new Spaz(id, name); }},
  };
  auto it = factories.find(player_id);
  return it != factories.end() ? it->second(player_id, player_name) : nullptr;
}

void Game::addPlayer(const PlayerInfo &player_info) {
  this->players++;
  std::string player_name(player_info.player_name.begin(),
                          player_info.player_name.end());
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
