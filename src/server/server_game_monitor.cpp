#include "server_game_monitor.h"
#include <mutex>

GameMonitor::GameMonitor() : players_count(0) {}

void GameMonitor::broadcast(const PlayerStatusDTO &msj) {
  std::lock_guard<std::mutex> lock(mtx);
  for (auto iter = this->queues.begin(); iter != this->queues.end(); iter++) {
    Queue<PlayerStatusDTO> &queue = iter->get();
    try {
      queue.push(msj);
    } catch (const ClosedQueue &) {
      iter = queues.erase(iter);
    }
  }
}

void GameMonitor::addPlayer(Queue<PlayerStatusDTO> &client) {
  std::lock_guard<std::mutex> lck(mtx);
  queues.push_back(client);
  players_count++;
}

void GameMonitor::ereasePlayer(const Queue<PlayerStatusDTO> &client) {
  std::lock_guard<std::mutex> lck(mtx);
  queues.remove_if(
      [&client](
          const std::reference_wrapper<Queue<PlayerStatusDTO>> &queue_ref) {
        return &queue_ref.get() == &client;
      });
  players_count--;
}