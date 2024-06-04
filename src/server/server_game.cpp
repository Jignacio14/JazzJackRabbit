#include "server_game.h"

Game::Game(GameMonitor &monitor) : monitor(monitor) {}

void Game::kill() { this->_is_alive = false; }
