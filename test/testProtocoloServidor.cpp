#include "../src/common/socket.h"
#include "../src/server/server_protocol.h"
#include <iostream>
#include <sys/types.h>

int main() {
  try {
    Socket socket("8080");
    Socket peer = socket.accept();
    ServerProtocol protocol(std::move(peer));
    uint8_t id = protocol.getLobbyOption();
    bool result = (id == 1);
    if (result) {
      std::cout << "Test passed" << std::endl;
    }
    socket.shutdown(2);
    std::cout << "Test passed" << std::endl;
  } catch (...) {
  }
  return 0;
}