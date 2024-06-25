#include "../src/common/socket.h"
#include "../src/server/server_protocol.h"
#include <iostream>
#include <sys/types.h>
#include <unordered_map>

#define EXPECTED_LOBBY_OPTION_RESEND 1
#define EXPECTED_LOBBY_OPTION_JOIN 2

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
    if (id == EXPECTED_LOBBY_OPTION_RESEND) {
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

void testEnviandoVariosComandos() {
  try {
    std::cout << std::endl;
    std::cout << "Testeando el protocolo del server - Caso Lobby" << std::endl;
    std::cout << "Mandando game info  - Caso Lobby" << std::endl;
    std::cout << std::endl;

    Socket socket("8080");
    Socket peer = socket.accept();
    ServerProtocol protocol(std::move(peer));
    uint8_t id = protocol.getLobbyOption();

    if (id == EXPECTED_LOBBY_OPTION_RESEND) {
      std::cout << GREEN << "He recibido el codigo esperado "
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No he recibido el codigo esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }

    id = protocol.getLobbyOption();

    if (id == EXPECTED_LOBBY_OPTION_JOIN) {
      std::cout << GREEN << "He recibido el codigo esperado "
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No he recibido el codigo esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }

    PlayerInfo info = protocol.getGameInfo();

    if (std::string(info.game_name) == "juego 1") {
      std::cout << GREEN << "He recibido el juego esperado "
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No he recibido el juego esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }

    if (std::string(info.player_name) == "username") {
      std::cout << GREEN << "He recibido el usuario esperado "
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No he recibido el usuario esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }

    if (info.character_code == 'J') {
      std::cout << GREEN << "He recibido el personaje esperado "
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No he recibido el personaje esperado " << RED
                << "TEST FAILED" << RESET << std::endl;
    }

  } catch (...) {
  }
}

int main() {
  testEnviandoInformacionJuegos();
  testEnviandoVariosComandos();
  return 0;
}