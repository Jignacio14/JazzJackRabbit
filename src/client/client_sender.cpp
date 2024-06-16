
#include "client_sender.h"

ClientSender::ClientSender(std::atomic<bool> &keep_talking,
                           Queue<std::vector<uint8_t>> &q,
                           ClientProtocol &protocol, uint8_t id)
    : keep_talking((keep_talking)), sender_queue(q), protocol(protocol),
      id(id) {}

void ClientSender::run() {
  try {
    bool was_closed = false;
    while (!was_closed && keep_talking) {
      std::vector<uint8_t> command = sender_queue.pop();
      CommandCodeDto command_code_dto;
      command_code_dto.player_id = id;
      command_code_dto.code = command[0];
      if (command.size() > 1)
        command_code_dto.data = command[1];
      else
        command_code_dto.data = 0;
      protocol.send_commands(was_closed, command_code_dto);
    }
  } catch (const ClosedQueue &e) {
  }
  keep_talking = false;
}

void ClientSender::kill() { keep_talking = false; }

ClientSender::~ClientSender() {}
