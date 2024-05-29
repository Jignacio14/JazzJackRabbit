#ifndef SERVER_PROTOCOL
#define SERVER_PROTOCOL

#include "../common/socket.h"
#include <atomic>
#include <utility>

class ServerProtocol {
private:
  Socket skt;
  std::atomic<bool> was_close;

public:
  explicit ServerProtocol(Socket skt);

  void shutdown();

  ~ServerProtocol();
};

#endif