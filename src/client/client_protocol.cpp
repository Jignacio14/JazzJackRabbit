
#include "client_protocol.h"
#include "../common/jjr2_error.h"
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

ClientProtocol::ClientProtocol(Socket &&socket) : skt(std::move(socket)) {}

void ClientProtocol::send_commands(bool &was_closed,
                                   const CommandCodeDto command_code_dto) {
  try {
    skt.sendall_bytewise(&command_code_dto, sizeof(CommandCodeDto),
                         &was_closed);
  } catch (const LibError &skt_err) {
    std::cout
        << "Some error ocurred while trying to send a message to the server."
        << std::endl;
  }
}

Snapshot ClientProtocol::deserializeSnapshot(const Snapshot &snapshot) {
  Snapshot finalSnapshot(snapshot);

  finalSnapshot.sizePlayers = ntohs(finalSnapshot.sizePlayers);
  finalSnapshot.sizeEnemies = ntohs(finalSnapshot.sizeEnemies);
  finalSnapshot.sizeCollectables = ntohs(finalSnapshot.sizeCollectables);
  finalSnapshot.sizeBullets = ntohs(finalSnapshot.sizeBullets);

  for (int i = 0; i < finalSnapshot.sizePlayers; i++) {
    finalSnapshot.players[i].points = ntohl(finalSnapshot.players[i].points);
    finalSnapshot.players[i].life = ntohs(finalSnapshot.players[i].life);
    finalSnapshot.players[i].position_x =
        ntohs(finalSnapshot.players[i].position_x);
    finalSnapshot.players[i].position_y =
        ntohs(finalSnapshot.players[i].position_y);
  }

  for (int i = 0; i < finalSnapshot.sizeEnemies; i++) {
    finalSnapshot.enemies[i].entity_id =
        ntohl(finalSnapshot.enemies[i].entity_id);
    finalSnapshot.enemies[i].position_x =
        ntohs(finalSnapshot.enemies[i].position_x);
    finalSnapshot.enemies[i].position_y =
        ntohs(finalSnapshot.enemies[i].position_y);
  }

  for (int i = 0; i < finalSnapshot.sizeBullets; i++) {
    finalSnapshot.bullets[i].entity_id =
        ntohl(finalSnapshot.bullets[i].entity_id);
    finalSnapshot.bullets[i].position_x =
        ntohs(finalSnapshot.bullets[i].position_x);
    finalSnapshot.bullets[i].position_y =
        ntohs(finalSnapshot.bullets[i].position_y);
  }

  for (int i = 0; i < finalSnapshot.sizeCollectables; i++) {
    finalSnapshot.collectables[i].entity_id =
        ntohl(finalSnapshot.collectables[i].entity_id);
    finalSnapshot.collectables[i].position_x =
        ntohs(finalSnapshot.collectables[i].position_x);
    finalSnapshot.collectables[i].position_y =
        ntohs(finalSnapshot.collectables[i].position_y);
  }

  return finalSnapshot;
}

Snapshot ClientProtocol::receive_snapshot(bool &was_closed) {
  try {
    Snapshot status;
    skt.recvall_bytewise(&status, sizeof(Snapshot), &was_closed);

    return this->deserializeSnapshot(status);
  } catch (const LibError &skt_err) {
    // throw LibError(errno, "Some error ocurred while trying to receive a "
    //                       "message from the server.");
    std::string errorMessage = "Some error ocurred while trying to receive a "
                               "message from the server.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
    // throw std::runtime_error("Some error ocurred while trying to receive a
    // message from the server.");
  }
}

void ClientProtocol::close_and_shutdown() {
  skt.shutdown(SHUT_RDWR);
  skt.close();
}
