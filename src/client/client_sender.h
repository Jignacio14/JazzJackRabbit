
#ifndef JAZZJACKRABBIT_CLIENT_SENDER_H
#define JAZZJACKRABBIT_CLIENT_SENDER_H

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include <atomic>
#include <iostream>

class ClientSender : public Thread {

private:
  std::atomic<bool> &keep_talking;
  // O quizas una queue de punteros al DTO?
  Queue<PlayerStatusDTO> &sender_queue;
  Socket &skt;

public:
  ClientSender(std::atomic<bool> &keep_talking, Queue<PlayerStatusDTO> &q,
               Socket &skt);
  void run() override;
};

#endif // JAZZJACKRABBIT_CLIENT_SENDER_H
