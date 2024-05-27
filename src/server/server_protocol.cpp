#include "server_protocol.h"
#include <cstdint>
#include <netinet/in.h>
#include <sys/types.h>
#include <vector>

#define HOW 2

ServerProtocol::ServerProtocol(Socket skt)
    : skt(std::move(skt)), was_close(false) {}

void ServerProtocol::sendGameInfo(
    const std::unordered_map<std::string, uint16_t> &game_info) {
  /// 1. Obtenego la cantidad de juegos dispobibles en las partidas registradas
  /// y lo envio

  uint16_t games_count = game_info.size();
  uint16_t games_count_formated = htons(games_count);
  skt.sendall_bytewise(&games_count_formated, sizeof(games_count_formated),
                       &was_close);
  if (was_close) {
    // throw err ?
    // En este caso no se si sera un error, creo que deberiamos preguntar, pero
    // probablemente lo sea
  }
  for (auto game : game_info) {
    //  Voy uno a uno los datos de la partida, obtengo lo siguiente 1. El nombre
    //  de la partida, 2. La cantidad de jugadores registrada
    //  3. La longitud del nombre del string
    std::string name = game.first;
    uint16_t player_number = game.second;
    uint16_t player_number_formatted = htons(player_number);
    uint8_t length = name.length();

    /// Como estoy trabajando con 2 bytes me aseguro de tener el endianess
    /// correcto y lo envio
    //  Envio la longitud del string para que el protocolo del cliente sepa lo
    //  que le viene
    skt.sendall_bytewise(&length, sizeof(length), &was_close);
    if (was_close) {
      // throw err
      // Aqui seguramente es un error porque algo paso en el medio
    }
    /// Formateo el string a vector char por comodidad para el envio y lo envio
    /// asi
    std::vector<char> data(name.begin(), name.end());
    skt.sendall_bytewise(data.data(), sizeof(data), &was_close);
    if (was_close) {
      // throw err
      // Seguramente esto es un error groso
    }
    skt.sendall_bytewise(&player_number_formatted,
                         sizeof(player_number_formatted), &was_close);
    if (was_close) {
      // throw err
    }
  }
}

void ServerProtocol::shutdown() {
  this->skt.shutdown(HOW);
  this->skt.close();
}