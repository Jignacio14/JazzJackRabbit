#ifndef RECEIVER
#define RECEIVER

#include "../common/thread.h"
#include "./server_protocol.h"

class Receiver : public Thread {
private:
  const ServerProtocol &servprot;

public:
  explicit Receiver(const ServerProtocol &servprot);
  void run() override;
  void kill();
  ~Receiver() override;
};

#endif
