#include "server_client_registrator.h"
#include "server_client_handler.h"
#include "server_games_monitor.h"
#include "server_protocol.h"
#include <utility>

Registrator::Registrator(Socket skt, GamesMonitor &monitor_ref)
    : servprot(std::move(skt)), monitor_ref(monitor_ref) {}

ClientHandler *Registrator::createClientHandler() {

  if (!this->sendGameList()) {
    return nullptr;
  }

  std::string game_name = this->receiveGameName();

  if (game_name.empty()) {
    return nullptr;
  }

  Queue<PlayerStatusDTO> &receiver_queue = this->getReceiverQueue(game_name);

  this->monitor_ref.registerUser(game_name, this->sender_queue);
  return new ClientHandler(std::move(this->sender_queue), receiver_queue,
                           std::move(this->servprot), this->monitor_ref);
}

bool Registrator::sendGameList() {
  auto games_info = this->monitor_ref.getGamesStatus();
  return this->servprot.sendGameInfo(games_info);
}

std::string Registrator::receiveGameName() {
  std::string game_name = this->servprot.getServerName();
  return game_name;
}

Queue<PlayerStatusDTO> &
Registrator::getReceiverQueue(const std::string &server_name) {
  Queue<PlayerStatusDTO> &receiver_queue =
      this->monitor_ref.getReceiverQueue(server_name);
  return receiver_queue;
}
