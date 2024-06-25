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
      std::cout << "He recibido el codigo esperado " << GREEN << "TEST PASSED"
                << RESET << std::endl;
    } else {
      std::cout << "No he recibido el codigo esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }
    std::cout << "Envio todos los juegos al cliente " << std::endl;
    protocol.sendGameInfo(games);
    std::cout << "Envio al cliente la cantidad de juegos que tiene el server"
              << std::endl;
    std::cout << "Se ha enviado correctamente la info al cliente: " << GREEN
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
      std::cout << "He recibido el codigo esperado " << GREEN << "TEST PASSED"
                << RESET << std::endl;
    } else {
      std::cout << "No he recibido el codigo esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }

    id = protocol.getLobbyOption();

    if (id == EXPECTED_LOBBY_OPTION_JOIN) {
      std::cout << "He recibido el codigo esperado " << GREEN << "TEST PASSED"
                << RESET << std::endl;
    } else {
      std::cout << "No he recibido el codigo esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }

    PlayerInfo info = protocol.getGameInfo();

    if (std::string(info.game_name) == "juego 1") {
      std::cout << "He recibido el juego esperado " << GREEN << "TEST PASSED"
                << RESET << std::endl;
    } else {
      std::cout << "No he recibido el juego esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }

    if (std::string(info.player_name) == "username") {
      std::cout << "He recibido el usuario esperado " << GREEN << "TEST PASSED"
                << RESET << std::endl;
    } else {
      std::cout << "No he recibido el usuario esperado " << RED << "TEST FAILED"
                << RESET << std::endl;
    }

    if (info.character_code == 'J') {
      std::cout << "He recibido el personaje esperado " << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No he recibido el personaje esperado " << RED
                << "TEST FAILED" << RESET << std::endl;
    }

  } catch (...) {
  }
}

void testRecibirVariosComandosCliente() {
  try {
    std::cout << std::endl;
    std::cout << "Teste de protocolo del cliente - Caso protocolo cliente"
              << std::endl;
    std::cout << std::endl;

    Socket socket("8080");
    Socket peer = socket.accept();
    ServerProtocol protocol(std::move(peer));

    CommandCodeDto dto1 = protocol.asyncGetEventCode();
    if (dto1.player_id == 1 && dto1.code == 1 && dto1.data == 1) {
      std::cout << "Prueba recibiendo el primer comando: " << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "Prueba recibiendo el primer comando: " << RED
                << "TEST FAILED" << RESET << std::endl;
    }
    CommandCodeDto dto2 = protocol.asyncGetEventCode();
    if (dto2.player_id == 3 && dto2.code == 2 && dto2.data == 1) {
      std::cout << "Prueba recibiendo el segundo comando: " << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "Prueba recibiendo el segundo comando: " << RED
                << "TEST FAILED" << RESET << std::endl;
    }

    CommandCodeDto dto3 = protocol.asyncGetEventCode();
    if (dto3.player_id == 11 && dto3.code == 8 && dto3.data == 3) {
      std::cout << "Prueba recibiendo el tercer comando: " << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "Prueba recibiendo el tercer comando: " << RED
                << "TEST FAILED" << RESET << std::endl;
    }

    socket.shutdown(2);
  } catch (...) {
  }
}

void testSendSnapShot() {
  try {
    std::cout << std::endl;
    std::cout << "Testeando enviar un snapshot" << std::endl;
    std::cout << std::endl;

    // Socket socket("8080");
    // std ::cout << "Esperando conexion" << std::endl;
    // Socket peer = socket.accept();
    // ServerProtocol protocol(std::move(peer));
    Socket socket("8080");
    Socket peer = socket.accept();
    ServerProtocol protocol(std::move(peer));

    PlayerDto jugador_test = {
        1, "jugador", 7, 0, 100, 1, 100, 100, 1, 1, 1,
        1, 1,         1, 2, 1,   1, 1,   1,   1, 1,
    };

    CollectableDto collectable_test = {
        1, 100, 100, 1, 1,
    };

    EnemyDto enemy_test = {
        1, 100, 100, 1, 1, 1, 1, 1,
    };

    BulletDto bullet_test = {
        1,
        100,
        100,
        1,
    };

    Snapshot snapshot_test = {
        100, 1,
        1,   {jugador_test},
        1,   {enemy_test},
        1,   {collectable_test},
        1,   {bullet_test},

    };

    protocol.sendSnapshot(snapshot_test);
    std::cout << "Se envio correctamente el snapshot" << GREEN << "TEST PASSED"
              << RESET << std::endl;

  } catch (...) {
  }
}
int main() {
  testEnviandoInformacionJuegos();
  testEnviandoVariosComandos();
  testRecibirVariosComandosCliente();
  testSendSnapShot();
  return 0;
}