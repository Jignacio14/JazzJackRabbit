#ifndef RECEIVER
#define RECEIVER

#include "../common/queue.h"
#include "../common/thread.h"
#include "./server_protocol.h"

class Receiver : public Thread {
private:
  ServerProtocol &servprot;
  // Queue<PlayerStatusDTO> &receiver_queue;

public:
  explicit Receiver(ServerProtocol &servprot);
  void run() override;
  void kill();
  ~Receiver() override;
};

#endif
