#ifndef SERVER
#define SERVER

#include "../common/thread.h"
#include "server_acceptator.h"
#include <iostream>

class Server : public Thread {
private:
  Acceptator acceptator;

public:
  explicit Server(const std::string &port);
  // Runs the server
  void run() override;

  ~Server();
};

#endif
