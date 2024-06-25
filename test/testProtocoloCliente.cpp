#include "../src/client/client_protocol.h"
#include "../src/client/lobby_protocol.h"
#include "../src/common/socket.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#define EXPECTED_GAMES 3
#define EXPECTED_GAME_NAME_1 "juego 1"
#define EXPECTED_PLAYER_COUNT_1 2
#define EXPECTED_GAME_NAME_2 "juego 2"
#define EXPECTED_PLAYER_COUNT_2 2
#define EXPECTED_GAME_NAME_3 "juego 3"
#define EXPECTED_PLAYER_COUNT_3 5
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void testRecibiendoInformacionDeJuegos() {
  std::cout << std::endl;
  std::cout << "Testeando el protocolo del cliente - Caso Lobby" << std::endl;
  std::cout << std::endl;

  Socket socket("localhost", "8080");
  LobbyProtocol lobby(std::ref(socket));
  lobby.send_refresh();

  std::cout << "Envio al server la solicitud de enviarme los juegos"
            << std::endl;
  uint16_t game_size = lobby.receive_header();
  std::cout << "Recibo del server la cantidad de juegos que tiene" << std::endl;

  if (game_size == EXPECTED_GAMES) {
    std::cout << "Recibo la cantidad de juegos pautada: " << GREEN
              << "TEST PASSED" << RESET << std::endl;
  } else {
    std::cout << "Recibo la cantidad de juegos pautada: " << RED
              << "TEST FAILED" << RESET << std::endl;
  }

  GameInfoDto game2 = lobby.receive_game();
  // std::cout << "Recibo del server el juego 2" << std::endl;
  // std::cout << "largo del string: " << game2.str_len << std::endl;
  // std::cout << "Nombre del juego: " << game2.game_name << std::endl;
  // std::cout << "Cantidad de jugadores: " << game2.player_count <<
  // std::endl;
  if (std::string(game2.game_name) == EXPECTED_GAME_NAME_2 &&
      game2.player_count == EXPECTED_PLAYER_COUNT_2) {
    std::cout << "Prueba de recibir el primer juego: " << GREEN << "TEST PASSED"
              << RESET << std::endl;
  } else {
    std::cout << "Prueba de recibir el primer juego: " << RED << "TEST FAILED"
              << RESET << std::endl;
  }

  GameInfoDto game3 = lobby.receive_game();
  if (std::string(game3.game_name) == EXPECTED_GAME_NAME_3 &&
      game3.player_count == EXPECTED_PLAYER_COUNT_3) {
    std::cout << "Prueba recibiendo el segundo juego: " << GREEN
              << "TEST PASSED" << RESET << std::endl;
  } else {
    std::cout << "Prueba recibiendo el segundo juego: " << RED << "TEST FAILED"
              << RESET << std::endl;
  }

  GameInfoDto game1 = lobby.receive_game();
  if (std::string(game1.game_name) == EXPECTED_GAME_NAME_1 &&
      game1.player_count == EXPECTED_PLAYER_COUNT_1) {
    std::cout << "Prueba recibiendo el tercer juego: " << GREEN << "TEST PASSED"
              << RESET << std::endl;
  } else {
    std::cout << "Prueba recibiendo el tercer juego: " << RED << "TEST FAILED"
              << std::endl;
  }
  std::cout << "Se ha recibido todo lo esperado del server" << std::endl;
}

void testRecibiendoVariosCommandos() {
  try {
    std::cout << std::endl;
    std::cout << "Testeando el protocolo del cliente - Caso Lobby" << std::endl;
    std::cout << "Mandando varios comandos al server" << std::endl;
    std::cout << std::endl;

    Socket socket("localhost", "8080");
    LobbyProtocol lobby(std::ref(socket));

    lobby.send_refresh();

    std::cout << "Se ha enviado el comando correctamente " << GREEN
              << "TEST PASSED" << RESET << std::endl;

    std::vector<char> game_name = {'j', 'u', 'e', 'g', 'o', ' ', '1'};
    std::vector<char> username = {'u', 's', 'e', 'r', 'n', 'a', 'm', 'e'};
    lobby.send_selected_game(game_name, 'J', username);

    std::cout << "Se envia correctamente la data del usuario " << GREEN
              << "TEST PASSED" << RESET << std::endl;
  } catch (...) {
  }
}

void testEnviandoVariosComandos() {
  std::cout << std::endl;
  std::cout << "Testeando el protocolo del server - Caso Lobby" << std::endl;
  std::cout << "Mandando game info  - Caso Lobby" << std::endl;
  std::cout << std::endl;

  Socket socket("localhost", "8080");
  ClientProtocol clientProt(std::move(socket));

  CommandCodeDto command_code_dto_1 = {1, 1, 1};
  CommandCodeDto command_code_dto_2 = {3, 2, 1};
  CommandCodeDto command_code_dto_3 = {11, 8, 3};

  std::cout << "Envio comandos al server" << std::endl;
  bool was_closed = false;
  clientProt.send_commands(was_closed, command_code_dto_1);
  if (was_closed) {
    std::cout << "Se ha cerrado la conexion" << RED << "TEST FAILED" << RESET
              << std::endl;
  } else {
    std::cout
        << "Se ha enviado correctamente la info del comando 1 al servidor: "
        << GREEN << "TEST PASSED" << RESET << std::endl;
  }
  clientProt.send_commands(was_closed, command_code_dto_2);
  if (was_closed) {
    std::cout << "Se ha cerrado la conexion" << RED << "TEST FAILED" << RESET
              << std::endl;
  } else {
    std::cout
        << "Se ha enviado correctamente la info del comando 2 al servidor: "
        << GREEN << "TEST PASSED" << RESET << std::endl;
  }
  clientProt.send_commands(was_closed, command_code_dto_3);
  if (was_closed) {
    std::cout << "Se ha cerrado la conexion" << RED << "TEST FAILED" << RESET
              << std::endl;
  } else {
    std::cout
        << "Se ha enviado correctamente la info del comando 3 al servidor: "
        << GREEN << "TEST PASSED" << RESET << std::endl;
  }
}

void testReceiveSnapshot() {
  try {
    std::cout << std::endl;
    std::cout << "Teste de recibir snapshot" << std::endl;
    std::cout << std::endl;
  } catch (...) {
  }
}

void testReceivedSnapshot() {
  try {
    std::cout << std::endl;
    std::cout << "Teste de recibir snapshot" << std::endl;
    std::cout << std::endl;

    Socket socket("localhost", "8080");
    ClientProtocol clientProt(std::move(socket));

    bool was_closed = false;
    Snapshot snapshot = clientProt.receive_snapshot(was_closed);

    if (was_closed) {
      std::cout << "Se ha cerrado la conexion" << RED << "TEST FAILED" << RESET
                << std::endl;
    } else {
      std::cout << "Se ha recibido correctamente el snapshot" << GREEN
                << "TEST PASSED" << RESET << std::endl;
    }

    if (snapshot.timeLeft == 100) {
      std::cout << "Se ha recibido correctamente el tiempo restante" << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente el tiempo restante" << RED
                << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.gameEnded) {
      std::cout << "Se ha recibido correctamente el fin del juego" << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente el fin del juego" << RED
                << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.sizePlayers == 1) {
      std::cout << "Se ha recibido correctamente la cantidad de jugadores"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente la cantidad de jugadores"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].user_id == 1) {
      std::cout << "Se ha recibido correctamente el id del jugador" << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente el id del jugador" << RED
                << "TEST FAILED" << RESET << std::endl;
    }

    if (std::string(snapshot.players[0].name) == "jugador") {
      std::cout << "Se ha recibido correctamente el nombre del jugador" << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente el nombre del jugador"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].nameSize == 7) {
      std::cout << "Se ha recibido correctamente el tamaño del nombre del "
                   "jugador"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente el tamaño del nombre del "
                   "jugador"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].points == 0) {
      std::cout << "Se ha recibido correctamente los puntos del jugador"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente los puntos del jugador"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].life == 100) {
      std::cout << "Se ha recibido correctamente la vida del jugador" << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente la vida del jugador" << RED
                << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].current_gun == 1) {
      std::cout << "Se ha recibido correctamente el arma actual del jugador"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente el arma actual del jugador"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].ammo_gun_1 == 100) {
      std::cout << "Se ha recibido correctamente la municion del arma 1 del "
                   "jugador"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente la municion del arma 1 del "
                   "jugador"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].ammo_gun_2 == 100) {
      std::cout << "Se ha recibido correctamente la municion del arma 2 del "
                   "jugador"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente la municion del arma 2 del "
                   "jugador"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].type == 1) {
      std::cout << "Se ha recibido correctamente el tipo de jugador" << GREEN
                << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente el tipo de jugador" << RED
                << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].is_falling == 1) {
      std::cout << "Se ha recibido correctamente si el jugador esta cayendo"
                << GREEN << "TEST PAS SED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente si el jugador esta cayendo"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].is_jumping == 1) {
      std::cout << "Se ha recibido correctamente si el jugador esta saltando"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout << "No se ha recibido correctamente si el jugador esta saltando"
                << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].is_walking == 1) {
      std::cout << "Se ha recibido correctamente si el jugador esta caminando"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout
          << "No se ha recibido correctamente si el jugador esta caminando"
          << RED << "TEST FAILED" << RESET << std::endl;
    }

    if (snapshot.players[0].is_running == 1) {
      std::cout << "Se ha recibido correctamente si el jugador esta corriendo"
                << GREEN << "TEST PASSED" << RESET << std::endl;
    } else {
      std::cout
          << "No se ha recibido correctamente si el jugador esta corriendo"
          << RED << "TEST FAILED" << RESET << std::endl;
    }

  } catch (...) {
    std::cout << "No se ha recibido correctamente el snapshot" << RED
              << "TEST FAILED" << RESET << std::endl;
  }
}

int main() {
  testRecibiendoInformacionDeJuegos();
  testRecibiendoVariosCommandos();
  testEnviandoVariosComandos();
  testReceivedSnapshot();
  return 0;
}