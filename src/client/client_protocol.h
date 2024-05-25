
#ifndef JAZZJACKRABBIT_CLIENT_PROTOCOL_H
#define JAZZJACKRABBIT_CLIENT_PROTOCOL_H

#include "../common/player_status_DTO.h"
#include "../common/socket.h"

class ClientProtocol {
private:
  Socket skt;
  std::atomic<bool> was_closed;

public:
  ClientProtocol(const char *hostname, const char *port);

  void send_status(bool &was_closed, PlayerStatusDTO status);
};

#endif // JAZZJACKRABBIT_CLIENT_PROTOCOL_H
