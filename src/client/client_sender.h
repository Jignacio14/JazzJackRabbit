
#ifndef JAZZJACKRABBIT_CLIENT_SENDER_H
#define JAZZJACKRABBIT_CLIENT_SENDER_H

#include "../common/thread.h"
#include <atomic>
#include <iostream>

class ClientSender : public Thread {
private:
  std::atomic<bool> &keep_talking;
  // queue

public:
  explicit ClientSender(std::atomic<bool> &keep_talking);
  void run() override;
};

#endif // JAZZJACKRABBIT_CLIENT_SENDER_H
