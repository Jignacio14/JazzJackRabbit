
#ifndef JAZZJACKRABBIT_CLIENT_RECEIVER_H
#define JAZZJACKRABBIT_CLIENT_RECEIVER_H

#include "../common/queue.h"
#include "../common/snapshot_DTO.h"
#include "../common/thread.h"
#include "client_protocol.h"
#include <atomic>
#include <iostream>

class ClientReceiver : public Thread {
private:
  std::atomic<bool> &keep_talking;

  ClientProtocol &protocol;

  Queue<Snapshot> &receiver_queue;

public:
  ClientReceiver(std::atomic<bool> &keep_talking, ClientProtocol &protocol,
                 Queue<Snapshot> &queue);

  void run() override;

  void kill();

  ~ClientReceiver() override;
};

#endif // JAZZJACKRABBIT_CLIENT_RECEIVER_H
