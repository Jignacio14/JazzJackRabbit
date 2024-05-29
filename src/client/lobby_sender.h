
#ifndef JAZZJACKRABBIT_LOBBY_SENDER_H
#define JAZZJACKRABBIT_LOBBY_SENDER_H

#include "../common/socket.h"
#include "../common/thread.h"
#include <atomic>
#include <iostream>

class LobbySender {

  Socket &skt;
  // cppcheck-suppress unusedStructMember
  bool &was_closed;

public:
  LobbySender(Socket &socket, bool &was_closed);

  void send_selected_game(const std::vector<char> &gamename);
};

#endif // JAZZJACKRABBIT_LOBBY_SENDER_H
