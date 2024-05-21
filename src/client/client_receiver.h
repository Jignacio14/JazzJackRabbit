
#ifndef JAZZJACKRABBIT_CLIENT_RECEIVER_H
#define JAZZJACKRABBIT_CLIENT_RECEIVER_H

#include "../common/thread.h"
#include <atomic>
#include <iostream>

class ClientReceiver : public Thread {
private:
  std::atomic<bool> &keep_talking;
  // queue

public:
  explicit ClientReceiver(std::atomic<bool> &keep_talking);
  void run() override;
};

#endif // JAZZJACKRABBIT_CLIENT_RECEIVER_H
