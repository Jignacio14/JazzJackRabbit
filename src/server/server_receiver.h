#ifndef RECEIVER
#define RECEIVER

#include "../common/queue.h"
#include "../common/snapshot_DTO.h"
#include "../common/thread.h"
#include "./server_protocol.h"
#include <sys/types.h>

class Receiver : public Thread {
private:
  ServerProtocol &servprot;
  Queue<u_int8_t> &receiver_queue;

public:
  explicit Receiver(ServerProtocol &servprot, Queue<u_int8_t> &receiver_queue);
  void run() override;
  void kill();
  ~Receiver() override;
};

#endif
