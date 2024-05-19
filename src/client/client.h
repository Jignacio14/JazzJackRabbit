
#ifndef JAZZJACKRABBIT_CLIENT_H
#define JAZZJACKRABBIT_CLIENT_H

#include "../common/queue.h"
#include "../common/socket.h"
#include "client_receiver.h"
#include "client_sender.h"
#include <atomic>

class Client {
private:
  int client_id;
  // Socket socket;
  std::atomic<bool> keep_talking;
  ClientSender client_sender;
  ClientReceiver client_receiver;
  // Queue<> queue_sender;
  // Queue<> queue_receiver;

public:
  explicit Client(int id);
};

#endif // JAZZJACKRABBIT_CLIENT_H
