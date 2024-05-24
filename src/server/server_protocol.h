#ifndef SERVER_PROTOCOL
#define SERVER_PROTOCOL

#include "../common/socket.h"
#include <utility>

class ServerProtocol {
private:
  Socket skt;

public:
  explicit ServerProtocol(Socket skt);

  void shutdown();

  ~ServerProtocol();
};

#endif