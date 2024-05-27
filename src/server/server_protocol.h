#ifndef SERVER_PROTOCOL
#define SERVER_PROTOCOL

#include "../common/socket.h"
#include <atomic>
#include <cstdint>
#include <netinet/in.h>
#include <string>
#include <unordered_map>
#include <utility>

class ServerProtocol {
private:
  Socket skt;
  // cppcheck-suppress unusedStructMember
  bool was_close;

  void sendGamesCount(const uint16_t &games_count);
  void sendStringLenght(const uint16_t &len);
  void sendGameName(const std::string &name);
  void sendGamePlayerCount(const uint16_t &count);

public:
  explicit ServerProtocol(Socket skt);

  void sendGameInfo(const std::unordered_map<std::string, uint16_t> &game_data);

  void shutdown();

  ~ServerProtocol();
};

#endif