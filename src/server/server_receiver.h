#ifndef RECEIVER
#define RECEIVER

#include "../common/queue.h"
#include "../common/snapshot_DTO.h"
#include "../common/thread.h"
#include "./server_protocol.h"
#include <sys/types.h>
#include <utility>

class Receiver : public Thread {
private:
  ServerProtocol &servprot;
  Queue<std::pair<u_int8_t, u_int8_t>> &receiver_queue;
  void recevierLoop();

public:
  explicit Receiver(ServerProtocol &servprot,
                    Queue<std::pair<u_int8_t, u_int8_t>> &receiver_queue);
  void run() override;
  void kill();
  ~Receiver() override;
};

#endif
