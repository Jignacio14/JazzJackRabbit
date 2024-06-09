#ifndef SERVER_PROTOCOL
#define SERVER_PROTOCOL

#include "../common/game_info.h"
#include "../common/liberror.h"
#include "../common/player_status_DTO.h"
#include "../common/socket.h"
#include "../data/player_info_dto.h"
#include "../data/snapshot_dto.h"
#include "./server_serializer.h"
#include <atomic>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <utility>

class ServerProtocol {
private:
  Socket skt;
  // cppcheck-suppress unusedStructMember
  std::atomic<bool> was_close;
  Serializer serializer;

  void sendGamesCount(const uint16_t &games_count);
  void sendSerializedGameData(const std::string &name, const uint16_t &count);
  const uint8_t getNameLenght();
  const std::vector<char> getName(const uint8_t &lenght);
  void throwIfClosed(const bool &result);
  const bool getTemporalWasClose();

public:
  explicit ServerProtocol(Socket skt);

  /// Metodos para el loby del sender

  bool sendGameInfo(const std::unordered_map<std::string, uint16_t> &game_data);

  const std::string getUserLobbyString();

  PlayerInfo getGameInfo();
  void sendPlayerId(const uint8_t &player_id);

  uint8_t getLobbyOption();
  std::pair<std::string, std::string> getGameNameAndPlayerName();

  std::pair<uint8_t, uint8_t> asyncGetEventCode();

  void sendSnapshot(const Snapshot &snapshot);

  void shutdown();

  ~ServerProtocol();
};

#endif