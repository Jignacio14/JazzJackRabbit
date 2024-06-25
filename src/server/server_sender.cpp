#include "./server_sender.h"
#include "./server_protocol.h"
#include "server_games_monitor.h"
#include "server_receiver.h"
#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <utility>

#define RESEND_GAME_INFO 1
#define REGISTER_PLAYER 2

Sender::Sender(Socket peer, GamesMonitor &games_monitor_ref)
    : servprot(std::move(peer)), gamesMonitor(games_monitor_ref), game_name(""),
      player_id(0) {}

void Sender::sendGamesOptions() {
  this->gamesMonitor.removeEndedGames();
  std::unordered_map<std::string, uint16_t> games =
      this->gamesMonitor.getGamesStartInfo();
  if (!this->servprot.sendGameInfo(games)) {
    throw std::runtime_error("Error en la comunicacion con el cliente");
  }
}

void Sender::savePlayerInfo(const PlayerInfo &player_info,
                            const uint8_t &player_id) {
  this->game_name = player_info.game_name;
  this->player_id = player_id;
}

Queue<CommandCodeDto> &Sender::setUpPlayerLoop() {
  while (true) {
    uint8_t option = this->servprot.getLobbyOption();
    if (option == RESEND_GAME_INFO) {
      this->sendGamesOptions();
      continue;
    }
    if (option == REGISTER_PLAYER) {
      PlayerInfo player_info = this->servprot.getGameInfo();
      this->ValidatePlayerInfo(player_info);
      std::pair<Queue<CommandCodeDto> &, uint8_t> result =
          this->gamesMonitor.registerPlayer(player_info, this->sender_queue);
      this->servprot.sendPlayerId(result.second);
      this->savePlayerInfo(player_info, result.second);
      // cppcheck-suppress returnReference
      return result.first;
    }
  }
}

void Sender::ValidatePlayerInfo(const PlayerInfo &player_info) {
  if (player_info.str_len == 0 ||
      player_info.character_code == PlayableCharactersIds::NoneSelected) {
    this->_is_alive = false;
    throw std::runtime_error("Error en la comunicacion con el cliente");
  }
}

void Sender::run() {
  try {
    this->sendGamesOptions();
    Queue<CommandCodeDto> &receiver_queue = this->setUpPlayerLoop();
    Receiver receiver(this->servprot, receiver_queue);
    receiver.start();
    this->runSenderLoop();
    receiver.kill();
    receiver.join();
  } catch (const JJR2Error &jjr2Err) {
    this->logOutPlayer();
    std::cerr << jjr2Err.what() << std::endl;
  } catch (const ClosedQueue &quErr) {
    this->logOutPlayer();
  } catch (const std::exception &error) {
    this->logOutPlayer();
    std::cerr << error.what() << std::endl;
  }
}

void Sender::runSenderLoop() {
  while (this->is_alive()) {
    Snapshot snapshot = this->sender_queue.pop();
    if (servprot.isShutedDown()) {
      this->logOutPlayer();
    }
    this->servprot.sendSnapshot(snapshot);
  }
}

void Sender::logOutPlayer() {
  this->gamesMonitor.removePlayer(this->game_name, this->player_id,
                                  this->sender_queue);
  this->_is_alive = false;
}

void Sender::kill() {
  try {
    this->_is_alive = false;
    this->sender_queue.close();
    this->servprot.shutdown();
  } catch (const LibError &sktErr) {
    // Para los posibles errores del shutdown
  } catch (const std::runtime_error &error) {
    // Por si trata de cerra la cola varias veces
  }
}

Sender::~Sender() {
  // try {
  //     this->_is_alive = false;
  //     std::cout << "Borrando el sender" << std::endl;
  //     // this->join();
  // } catch (const std::exception& err) {
  //   std::cerr << "Pase por aqui de manera barbara" << std::endl;
  // }
}
