#ifndef SERVER_ACCEPTATOR
#define SERVER_ACCEPTATOR

#include "../common/socket.h"
#include "../common/thread.h"
#include <string>

class Acceptator : public Thread {
private:
  Socket skt_aceptator;
  void accept();

public:
  explicit Acceptator(const std::string &port);
  void run() override;
  void kill();
  ~Acceptator();
};
#endif
