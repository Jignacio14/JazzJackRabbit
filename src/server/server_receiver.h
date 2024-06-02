#ifndef RECEIVER
#define RECEIVER

#include "../common/queue.h"
#include "../common/thread.h"
#include "../data/base_dto.h"
#include "./server_protocol.h"

class Receiver : public Thread {
private:
  ServerProtocol &servprot;
  Queue<BaseDTO *> &receiver_queue;

public:
  explicit Receiver(ServerProtocol &servprot, Queue<BaseDTO *> &receiver_queue);
  void run() override;
  void kill();
  ~Receiver() override;
};

#endif
