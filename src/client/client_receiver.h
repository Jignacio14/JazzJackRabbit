
#ifndef JAZZJACKRABBIT_CLIENT_RECEIVER_H
#define JAZZJACKRABBIT_CLIENT_RECEIVER_H

#include "../common/thread.h"
#include "client_protocol.h"
#include <atomic>
#include <iostream>

class ClientReceiver : public Thread {
private:
  std::atomic<bool> &keep_talking;

  ClientProtocol &protocol;

  // queue

public:
  ClientReceiver(std::atomic<bool> &keep_talking, ClientProtocol &protocol);
  void run() override;
};

#endif // JAZZJACKRABBIT_CLIENT_RECEIVER_H
