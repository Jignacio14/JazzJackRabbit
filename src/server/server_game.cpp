#include "server_game.h"
#include <iostream>
#include <thread>
#define MIN_PLAYERS 2

Game::Game(GameMonitor &monitor, Queue<BaseDTO *> &queue)
    : monitor(monitor), messages(queue), players(0) {}

void Game::waitingRoomLoop() {
  while (this->players < MIN_PLAYERS) {
  }
}

void Game::gameLoop() {
  while (this->_is_alive) {
    /// Empiezo a calcular la diferencia de tiempo para hacer el sleep
    BaseDTO *dto;
    if (!this->messages.try_pop(dto)) {
      continue;
    }
    this->executeAction(dto);
    delete dto;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void Game::executeAction(BaseDTO *dto) {
  std::cout << "Executing action" << std::endl;
}

void Game::run() {
  this->waitingRoomLoop();
  this->gameLoop();
}

void Game::addPlayer(const PlayerInfo &player_info) {
  this->players++;
  std::cout << "Player added" << std::endl;
}

void Game::kill() { this->_is_alive = false; }
