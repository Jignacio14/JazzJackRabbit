#include "server_client_handler.h"
#include "server_games_monitor.h"
#include "server_receiver.h"
#include "server_sender.h"

ClientHandler::ClientHandler(Socket skt, GamesMonitor &monitor_ref)
    : servprot(std::move(skt)), receiver(servprot), sender(servprot),
      monitor(monitor_ref) {}

void ClientHandler::start() {
  // TO-DO:
  // Agregar aca la logica del registro, que no sea de los hilos !!! eso es una
  // tarea secuencial !!!!!!!!!
  auto games_state = this->monitor.getGamesStatus();
  this->servprot.sendGameInfo(games_state);

  this->receiver.start();
  this->sender.start();
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