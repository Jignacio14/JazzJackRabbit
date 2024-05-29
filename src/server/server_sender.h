#ifndef SENDER
#define SENDER

#include "../common/thread.h"
#include "server_protocol.h"

class Sender : public Thread {
private:
  ServerProtocol &servprot;
  void sendGameInfo();
  void runSenderLoop();

public:
  explicit Sender(ServerProtocol &servprot);

  void run() override;

  void kill();

  ~Sender();
};

#endif