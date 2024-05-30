#ifndef SENDER
#define SENDER

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../common/thread.h"
#include "server_protocol.h"

class Sender : public Thread {
private:
  ServerProtocol &servprot;
  Queue<PlayerStatusDTO> &queue;
  void sendGameInfo();
  void runSenderLoop();

public:
  explicit Sender(ServerProtocol &servprot, Queue<PlayerStatusDTO> &queue);

  void run() override;

  void kill();

  ~Sender();
};

#endif