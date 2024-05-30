#ifndef SERVER_PROTOCOL
#define SERVER_PROTOCOL

#include "../common/game_info.h"
#include "../common/liberror.h"
#include "../common/player_status_DTO.h"
#include "../common/socket.h"
#include "./server_serializer.h"
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

class ServerProtocol {
private:
  Socket skt;
  // cppcheck-suppress unusedStructMember
  bool was_close;

  Serializer serializer;

  void sendGamesCount(const uint16_t &games_count);
  void sendSerializedGameData(const std::string &name, const uint16_t &count);
  const uint8_t getNameLenght();
  const std::vector<char> getName(const uint8_t &lenght);

public:
  explicit ServerProtocol(Socket skt);

  bool sendGameInfo(const std::unordered_map<std::string, uint16_t> &game_data);
  const std::string getServerName();
  void sendGameStatus(const PlayerStatusDTO &dto);
  const PlayerStatusDTO getGameStatus();
  void shutdown();

  ~ServerProtocol();
};

#endif