#include "server_client_handler.h"
#include "server_games_monitor.h"
#include "server_receiver.h"
#include "server_sender.h"

ClientHandler::ClientHandler(Socket skt, GamesMonitor &monitor_ref)
    : servprot(std::move(skt)), receiver(servprot), sender(servprot),
      monitor(monitor_ref), can_run(true) {}

void ClientHandler::start() {
  // TO-DO:
  // Agregar aca la logica del registro, que no sea de los hilos !!! eso es una
  // tarea secuencial !!!!!!!!!
  this->receiver.start();
  this->sender.start();
}

std::string ClientHandler::loginSetUp() {
  std::unordered_map<std::string, u_int16_t> games_state =
      this->monitor.getGamesStatus();
  this->can_run = this->servprot.sendGameInfo(games_state);
  // std::string game_name = this->servprot.
  std::string game_name = this->servprot.getServerName();
  return game_name;
}

const bool ClientHandler::running() {
  return this->receiver.is_alive() && this->sender.is_alive();
}

void ClientHandler::stop() {
  this->servprot.shutdown();
  this->receiver.kill();
  this->receiver.join();
  this->sender.kill();
  this->sender.join();
}

ClientHandler::~ClientHandler() {}