#include "./ui/startup_screen.h"
#include "lobby.h"
#include "renderer.h"
#include <cstdint>
#include <iostream>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

const static int EXIT_SUCCESS_CODE = 0;
const static int EXIT_ERROR_CODE = -1;

const static char CHARACTER_NOT_SELECTED = '0';
const static char JAZZ_SELECTED = 'J';
const static char SPAZ_SELECTED = 'S';
const static char LORI_SELECTED = 'L';

int main(int argc, char *argv[]) {

  const uint8_t EXPECTED_ARGUMENTS = 1;

  if (argc != EXPECTED_ARGUMENTS) {
    const std::string errorMessage = "Error while calling program. Expected " +
                                     std::string(argv[0]) +
                                     " call with no extra arguments";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  std::string hostname("");
  uint32_t port(0);
  std::string username("");
  char userCharacter = CHARACTER_NOT_SELECTED;
  GameConfigs game;
  GameConfigs *gamePtr = &game;

  StartupScreen startupScreen(argc, argv, hostname, port, username, gamePtr,
                              userCharacter);

  int exitCode = startupScreen.show();

  if (exitCode != EXIT_SUCCESS_CODE) {
    const std::string errorMessage =
        "Error while closing StartupScreen. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  if (game.getOwnerName().empty()) {
    const std::string errorMessage = "After closing StartupScreen no game "
                                     "configs loaded correctly. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  if (userCharacter == CHARACTER_NOT_SELECTED) {
    const std::string errorMessage =
        "After closing StartupScreen no character selected. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  std::cout << username << "\n";
  std::cout << userCharacter << "\n";
  std::cout << game.getOwnerName() << "|" << game.getCurrentNumberOfPlayers()
            << "/" << game.getMaxNumberOfPlayers() << "\n";
  std::cout << hostname << ":" << port << std::endl;

  Lobby lobby(hostname.c_str(), std::to_string(port).c_str());
  std::vector<GameInfoDto> game = lobby.get_games();

  std::vector<char> gamename(10); // hardcodeado
  lobby.send_selected_game(gamename);

  Socket skt = lobby.transfer_socket();
  int client_id;
  Renderer renderer(client_id, skt);
  renderer.run();

  return exitCode;
}
