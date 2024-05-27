#include "server_protocol.h"
#include "server_game_info_dto.h"
#include "server_serializer.h"
#include <cstdint>
#include <netinet/in.h>
#include <string>
#include <sys/types.h>

#define HOW 2

ServerProtocol::ServerProtocol(Socket skt)
    : skt(std::move(skt)), was_close(false), serializer() {}

void ServerProtocol::sendGameInfo(
    const std::unordered_map<std::string, uint16_t> &game_info) {

  this->sendGamesCount(game_info.size());
  for (auto game : game_info) {
    //  Voy uno a uno los datos de la partida, obtengo lo siguiente 1. El nombre
    //  de la partida, 2. La cantidad de jugadores registrada
    //  3. La longitud del nombre del string
    this->sendSerializedGameData(game.first, game.second);
  }
}

void ServerProtocol::sendGamesCount(const uint16_t &games_count) {
  /// 1. Obtenego la cantidad de juegos dispobibles en las partidas registradas
  /// y lo envio
  uint16_t games_count_formated = htons(games_count);
  skt.sendall_bytewise(&games_count_formated, sizeof(games_count_formated),
                       &was_close);
  if (was_close) {
    // throw err ?
    // En este caso no se si sera un error, creo que deberiamos preguntar, pero
    // probablemente lo sea
  }
}

void ServerProtocol::sendSerializedGameData(const std::string &name,
                                            const uint16_t &count) {
  GameInfoDto data = this->serializer.serializeGameInfo(name, count);
  skt.sendall_bytewise(&data, sizeof(data), &was_close);
  if (was_close) {
  }
}

void ServerProtocol::shutdown() {
  this->skt.shutdown(HOW);
  this->skt.close();
}