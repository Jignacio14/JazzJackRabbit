
#ifndef JAZZJACKRABBIT_CLIENT_PROTOCOL_H
#define JAZZJACKRABBIT_CLIENT_PROTOCOL_H

#include "../common/liberror.h"
#include "../common/player_status_DTO.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "../data/command_code_dto.h"
#include "../data/snapshot_dto.h"
#include <atomic>

class ClientProtocol {
private:
  Socket skt;

public:
  explicit ClientProtocol(Socket &&socket);

  void send_commands(bool &was_closed, const CommandCodeDto command_code_dto);

  Snapshot receive_snapshot(bool &was_closed);

  void close_and_shutdown();
};

#endif // JAZZJACKRABBIT_CLIENT_PROTOCOL_H
