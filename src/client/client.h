
#ifndef JAZZJACKRABBIT_CLIENT_H
#define JAZZJACKRABBIT_CLIENT_H

#include "../common/queue.h"
#include "../common/socket.h"
#include "client_receiver.h"
#include "client_sender.h"
#include <atomic>

class Client {
private:
  // cppcheck-suppress unusedStructMember
  int client_id;
  Socket socket;
  std::atomic<bool> keep_talking;
  ClientSender sender;
  ClientReceiver receiver;
  Queue<PlayerStatusDTO> sender_queue;
  // Queue<> queue_receiver;

public:
  Client(Socket &&skt, int id);

  /*
   * Kills the client´s back-end, joining receiver and sender thread, and closes
   * the socket.
   */
  void kill();
};

#endif // JAZZJACKRABBIT_CLIENT_H
