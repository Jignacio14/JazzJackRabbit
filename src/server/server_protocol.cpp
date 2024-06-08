#include "./server_protocol.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

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

const std::string ServerProtocol::getUserLobbyString() {
  try {
    uint16_t lenght = this->getNameLenght();
    std::vector<char> name = this->getName(lenght);
    return std::string(name.begin(), name.end());
  } catch (const LibError &skt_err) {
    std::cout << "Some error ocurred while trying to communicate" << std::endl;
    return "";
  }
}

void ServerProtocol::sendGamesCount(const uint16_t &games_count) {
  /// 1. Obtenego la cantidad de juegos dispobibles en las partidas registradas
  /// y lo envio
  bool wasClose = this->getTemporalWasClose();
  uint16_t games_count_formated = htons(games_count);
  skt.sendall_bytewise(&games_count_formated, sizeof(games_count_formated),
                       &wasClose);
  this->throwIfClosed(wasClose);
}

void ServerProtocol::sendSerializedGameData(const std::string &name,
                                            const uint16_t &count) {

  // Utilizo un dto para enviar la data, seguamente me falta poner packed o algo
  // asi pero para ir maquetando la solucion viene perfecto, si esto falla,
  // falla en un solo lugar y no tenog que estar rastrando que fue lo que se
  // rompio con los 3 tipos de datos distintos que debo pasar al cliente
  bool wasClose = this->getTemporalWasClose();
  GameInfoDto data = this->serializer.serializeGameInfo(name, count);
  skt.sendall_bytewise(&data, sizeof(data), &wasClose);
  this->throwIfClosed(wasClose);
}

const uint8_t ServerProtocol::getNameLenght() {
  bool wasClose = this->getTemporalWasClose();
  uint8_t lenght;
  this->skt.recvall_bytewise(&lenght, sizeof(lenght), &wasClose);
  this->throwIfClosed(wasClose);
  return lenght;
}

const std::vector<char> ServerProtocol::getName(const uint8_t &lenght) {
  bool wasClose = this->getTemporalWasClose();
  std::vector<char> vector(lenght);
  this->skt.recvall_bytewise(vector.data(), sizeof(vector), &wasClose);
  this->throwIfClosed(wasClose);
  return vector;
}

PlayerInfo ServerProtocol::getGameInfo() {
  bool wasClose = this->getTemporalWasClose();
  PlayerInfo info;
  this->skt.recvall_bytewise(&info, sizeof(info), &wasClose);
  this->throwIfClosed(wasClose);
  return info;
}

uint8_t ServerProtocol::getLobbyOption() {
  bool wasClose = this->getTemporalWasClose();
  uint8_t option;
  this->skt.recvall_bytewise(&option, sizeof(option), &wasClose);
  this->throwIfClosed(wasClose);
  return option;
}

std::pair<std::string, std::string> ServerProtocol::getGameNameAndPlayerName() {
  try {
    uint8_t lenght = this->getNameLenght();
    std::vector<char> name = this->getName(lenght);
    lenght = this->getNameLenght();
    std::vector<char> map = this->getName(lenght);
    return std::make_pair(std::string(name.begin(), name.end()),
                          std::string(map.begin(), map.end()));
  } catch (const LibError &skt_err) {
    std::cout << "Some error ocurred while trying to communicate" << std::endl;
    return std::make_pair("", "");
  }
}

void ServerProtocol::sendPlayerId(const uint8_t &player_id) {
  bool wasClose = this->getTemporalWasClose();
  skt.sendall_bytewise(&player_id, sizeof(player_id), &wasClose);
  this->throwIfClosed(wasClose);
}

const bool ServerProtocol::getTemporalWasClose() {
  return this->was_close.load();
}

void ServerProtocol::throwIfClosed(const bool &result) {
  if (result) {
    this->was_close.store(true);
    throw LibError(errno, "Socket closed");
  }
}

std::pair<uint8_t, uint8_t> ServerProtocol::asyncGetEventCode() {
  bool wasClose = this->getTemporalWasClose();
  uint8_t buf[2];
  this->skt.recvall_bytewise(&buf, sizeof(buf), &wasClose);
  this->throwIfClosed(wasClose);
  return std::make_pair(buf[0], buf[1]);
}

void ServerProtocol::sendSnapshot(const Snapshot &snapshot) {
  bool wasClose = this->getTemporalWasClose();
  this->skt.sendall_bytewise(&snapshot, sizeof(snapshot), &wasClose);
  this->throwIfClosed(wasClose);
}

void ServerProtocol::shutdown() {
  this->skt.shutdown(HOW);
  this->skt.close();
}

ServerProtocol::~ServerProtocol() {}
