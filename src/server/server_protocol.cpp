#include "server_protocol.h"

#define HOW 2

ServerProtocol::ServerProtocol(Socket skt)
    : skt(std::move(skt)), was_close(false), serializer() {}

bool ServerProtocol::sendGameInfo(
    const std::unordered_map<std::string, uint16_t> &game_info) {
  try {
    this->sendGamesCount(game_info.size());
    for (auto game : game_info) {
      //  Voy uno a uno los datos de la partida, obtengo lo siguiente 1. El
      //  nombre de la partida, 2. La cantidad de jugadores registrada
      //  3. La longitud del nombre del string
      this->sendSerializedGameData(game.first, game.second);
    }
    return true;
  } catch (const LibError &skt_err) {
    std::cout << "Some error ocurred while trying to communicate" << std::endl;
    return false;
  }
}

void ServerProtocol::sendGamesCount(const uint16_t &games_count) {
  /// 1. Obtenego la cantidad de juegos dispobibles en las partidas registradas
  /// y lo envio
  uint16_t games_count_formated = htons(games_count);
  skt.sendall_bytewise(&games_count_formated, sizeof(games_count_formated),
                       &was_close);
}

void ServerProtocol::sendSerializedGameData(const std::string &name,
                                            const uint16_t &count) {

  // Utilizo un dto para enviar la data, seguamente me falta poner packed o algo
  // asi pero para ir maquetando la solucion viene perfecto, si esto falla,
  // falla en un solo lugar y no tenog que estar rastrando que fue lo que se
  // rompio con los 3 tipos de datos distintos que debo pasar al cliente
  GameInfoDto data = this->serializer.serializeGameInfo(name, count);
  skt.sendall_bytewise(&data, sizeof(data), &was_close);
}

void ServerProtocol::shutdown() {
  this->skt.shutdown(HOW);
  this->skt.close();
}