// #include "../src/client/client_protocol.h"
#include "../src/client/lobby_protocol.h"
#include "../src/common/socket.h"

int main() {
  try {
    Socket socket("localhost", "8080");
    LobbyProtocol lobby(std::ref(socket));
    lobby.send_refresh();
    socket.shutdown(2);
  } catch (...) {
  }
  return 0;
}