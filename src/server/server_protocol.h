#ifndef SERVER_PROTOCOL
#define SERVER_PROTOCOL

#include "../common/socket.h"
#include <atomic>
#include <netinet/in.h>
#include <string>
#include <unordered_map>
#include <utility>

class ServerProtocol {
private:
  Socket skt;
  // cppcheck-suppress unusedStructMember
  bool was_close;

public:
  explicit ServerProtocol(Socket skt);

  void sendGameInfo(const std::unordered_map<std::string, uint16_t> &game_data);

  void shutdown();

  ~ServerProtocol();
};

#endif