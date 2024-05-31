#ifndef SERVER_ACCEPTATOR
#define SERVER_ACCEPTATOR

#include "../common/socket.h"
#include "../common/thread.h"
#include "./server_games_monitor.h"
#include "server_sender.h"
#include <exception>
#include <list>
#include <string>

class Accepter : public Thread {
private:
  Socket skt_aceptator;
  void accept();
  // cppcheck-suppress unusedStructMember
  std::list<Sender *> clients;
  GamesMonitor gamesMonitor;

  void checkForDisconnected();
  void killAll();

public:
  explicit Accepter(const std::string &port);
  void run() override;
  void kill();
  ~Accepter() override;
  // cppcheck-suppress syntaxError
};
#endif
