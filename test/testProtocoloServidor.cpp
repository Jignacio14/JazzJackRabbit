#include "../src/common/socket.h"
#include "../src/server/server_protocol.h"
#include <iostream>
#include <sys/types.h>
#include <unordered_map>

#define EXPECTED_LOBBY_OPTION 1

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void testEnviandoInformacionJuegos() {
  try {
    std::cout << std::endl;
    std::cout << "Testeando el protocolo del server - Caso Lobby" << std::endl;
    std::cout << "Mandando game info  - Caso Lobby" << std::endl;
    std::cout << std::endl;

    std::unordered_map<std::string, u_int16_t> games = {
        {"juego 1", 2},
        {"juego 2", 2},
        {"juego 3", 5},
    };

    Socket socket("8080");
    Socket peer = socket.accept();
    ServerProtocol protocol(std::move(peer));
    uint8_t id = protocol.getLobbyOption();
    if (id == EXPECTED_LOBBY_OPTION) {
      std::cout << GREEN << "He recibido el codigo esperado "
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No he recibido el codigo esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }
    std::cout << "Envio todos los juegos al cliente " << std::endl;
    protocol.sendGameInfo(games);
    std::cout << "Envio al cliente la cantidad de juegos que tiene el server"
              << std::endl;
    std::cout << GREEN << "Se ha enviado correctamente la info al cliente: "
              << "TEST PASSED" << RESET << std::endl;
    socket.shutdown(2);
  } catch (...) {
  }
}

int main() {
  testEnviandoInformacionJuegos();
  return 0;
}