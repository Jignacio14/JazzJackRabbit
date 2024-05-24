#ifndef RECEIVER
#define RECEIVER

#include "../common/thread.h"
#include "server_protocol.h"

// cppcheck-suppress noConstructor
class Receiver : public Thread {
private:
  const ServerProtocol &servprot;

  // cppcheck-suppress noExplicitConstructor
public:
  // cppcheck-suppress noExplicitConstructor
  explicit Receiver(const ServerProtocol &servprot);
  void run() override;
  void kill();
  ~Receiver();
};

#endif
