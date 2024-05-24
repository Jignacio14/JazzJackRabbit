#ifndef SENDER
#define SENDER

#include "../common/thread.h"
#include "server_protocol.h"

class Sender : public Thread {
private:
  const ServerProtocol &servprot;

public:
  explicit Sender(const ServerProtocol &servprot);

  void run() override;

  void kill();

  ~Sender();
};

#endif