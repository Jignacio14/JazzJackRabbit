
#ifndef JAZZJACKRABBIT_CLIENT_SENDER_H
#define JAZZJACKRABBIT_CLIENT_SENDER_H

#include "../common/queue.h"
#include "../common/thread.h"
#include "client_protocol.h"
#include <atomic>
#include <iostream>

class ClientSender : public Thread {

private:
  std::atomic<bool> &keep_talking;
  // O quizas una queue de punteros al DTO?
  Queue<PlayerStatusDTO> &sender_queue;
  ClientProtocol &protocol;

public:
  ClientSender(std::atomic<bool> &keep_talking, Queue<PlayerStatusDTO> &q,
               ClientProtocol &protocol);
  void run() override;
};

#endif // JAZZJACKRABBIT_CLIENT_SENDER_H
