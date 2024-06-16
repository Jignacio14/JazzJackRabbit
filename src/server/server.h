#ifndef SERVER
#define SERVER
#include "../common/thread.h"
#include "server_accepter.h"
#include <iostream>

class Server {
private:
  Accepter acceptator;

public:
  explicit Server(const std::string &port);
  // Runs the server
  void run();

  ~Server();

  void kill();
  // cppcheck-suppress syntaxError
};
#endif
