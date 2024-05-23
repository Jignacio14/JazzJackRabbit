#ifndef SENDER
#define SENDER

#include "../common/thread.h"
#include "server_protocol.h"

class Sender : public Thread {
private:
  // ServerProtocol servprot;

public:
  explicit Sender();

  void run() override;

  ~Sender();
};

#endif