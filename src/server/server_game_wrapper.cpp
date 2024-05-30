#include "server_game_wrapper.h"

GameWrapper::GameWrapper() : monitor() {}

void GameWrapper::registerPlayer(Queue<PlayerStatusDTO> &sender_queue) {
  monitor.addPlayer(sender_queue);
}

Queue<PlayerStatusDTO> &GameWrapper::getReceiverQueue() {
  return this->messages;
}