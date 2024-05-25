
#include "client_protocol.h"

ClientProtocol::ClientProtocol(const char *hostname, const char *port)
    : skt(hostname, port), was_closed(false) {}

void ClientProtocol::send_status(bool &was_closed, PlayerStatusDTO status) {
  skt.sendall_bytewise(&status, sizeof(PlayerStatusDTO), &was_closed);
}
