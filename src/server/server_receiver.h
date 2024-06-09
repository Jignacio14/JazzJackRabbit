#ifndef RECEIVER
#define RECEIVER

#include "../common/queue.h"
#include "../common/thread.h"
#include "../data/command_code_dto.h"
#include "../data/snapshot_dto.h"
#include "./server_protocol.h"
#include <sys/types.h>
#include <utility>

class Receiver : public Thread {
private:
  ServerProtocol &servprot;
  Queue<CommandCodeDto> &receiver_queue;
  void recevierLoop();

public:
  explicit Receiver(ServerProtocol &servprot,
                    Queue<CommandCodeDto> &receiver_queue);
  void run() override;
  void kill();
  ~Receiver() override;
};

#endif
