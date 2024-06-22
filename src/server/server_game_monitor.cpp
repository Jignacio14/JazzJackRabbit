#include "server_game_monitor.h"

GameMonitor::GameMonitor() : players_count(0) {}

void GameMonitor::broadcast(const Snapshot &msj) {
  std::lock_guard<std::mutex> lock(mtx);
  for (auto iter = this->queues.begin(); iter != this->queues.end(); iter++) {
    Queue<Snapshot> &queue = iter->get();
    try {
      queue.push(msj);
    } catch (const ClosedQueue &) {
      iter = queues.erase(iter);
      this->ereasePlayer(queue);
    }
  }
}

const u_int8_t GameMonitor::addPlayer(const PlayerInfo &player_info,
                                      Queue<Snapshot> &client) {
  std::lock_guard<std::mutex> lck(mtx);
  queues.push_back(client);
  players_count++;
  return players_count;
}

void GameMonitor::ereasePlayer(const Queue<Snapshot> &client) {
  std::lock_guard<std::mutex> lck(mtx);
  queues.remove_if(
      [&client](const std::reference_wrapper<Queue<Snapshot>> &queue_ref) {
        return &queue_ref.get() == &client;
      });
  players_count--;
}

GameMonitor::~GameMonitor() {}
