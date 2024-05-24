#ifndef SERVER_ACCEPTATOR
#define SERVER_ACCEPTATOR

#include "../common/socket.h"
#include "../common/thread.h"
#include "server_client_handler.h"
#include <exception>
#include <list>
#include <string>

class Acceptator : public Thread {
private:
  Socket skt_aceptator;
  void accept();
  // cppcheck-suppress unusedStructMember
  std::list<ClientHandler *> clients;

  void checkForDisconnected();
  void killAll();

public:
  explicit Acceptator(const std::string &port);
  void run() override;
  void kill();
  ~Acceptator();
};
#endif
