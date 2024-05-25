
#ifndef JAZZJACKRABBIT_CLIENT_PROTOCOL_H
#define JAZZJACKRABBIT_CLIENT_PROTOCOL_H

#include "../common/player_status_DTO.h"
#include "../common/snapshot_DTO.h"
#include "../common/socket.h"

class ClientProtocol {
private:
  Socket skt;
  std::atomic<bool> was_closed;

public:
  ClientProtocol(const char *hostname, const char *port);

  void send_status(bool &was_closed, PlayerStatusDTO status);

  void receive_snapshot(bool &was_closed, Snapshot &status);
};

#endif // JAZZJACKRABBIT_CLIENT_PROTOCOL_H
