
#ifndef JAZZJACKRABBIT_CLIENT_PROTOCOL_H
#define JAZZJACKRABBIT_CLIENT_PROTOCOL_H

#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "../data/snapshot_dto.h"
#include <atomic>

class ClientProtocol {
private:
  Socket skt;

public:
  explicit ClientProtocol(Socket &&socket);

  void send_status(bool &was_closed, const std::vector<uint8_t> &command);

  Snapshot receive_snapshot(bool &was_closed);

  void send_id(bool &was_closed, const uint8_t id);

  void close_and_shutdown();
};

#endif // JAZZJACKRABBIT_CLIENT_PROTOCOL_H
