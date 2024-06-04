#include "./game_configs.h"
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

const static bool TEST_ONLY_SDL_MODE = true;

void debugPrint(std::string &hostname, uint32_t &port, std::string &username,
                char &userCharacter, GameConfigs &gameConfig) {
  std::cout << "username: " << username << "\n";
  std::cout << "character selected: " << userCharacter << "\n";
  std::cout << "Owner name: " << gameConfig.getOwnerName() << "|"
            << " Players: " << gameConfig.getCurrentNumberOfPlayers() << "/"
            << gameConfig.getMaxNumberOfPlayers() << "\n";
  std::cout << "Hostname and port: " << hostname << ":" << port << std::endl;
}

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
  // cppcheck-suppress unreadVariable
  uint32_t port(0);
  std::string username("");
  char userCharacter = CHARACTER_NOT_SELECTED;
  GameConfigs gameConfig;
  GameConfigs *gamePtr = &gameConfig;

  int exitCode = 0;

  if (TEST_ONLY_SDL_MODE == false) {
    StartupScreen startupScreen(argc, argv, hostname, port, username, gamePtr,
                                userCharacter);

    exitCode = startupScreen.show();

    if (exitCode != EXIT_SUCCESS_CODE) {
      return EXIT_ERROR_CODE;
    }
  }

  debugPrint(hostname, port, username, userCharacter, gameConfig);

  Lobby lobby(hostname.c_str(), std::to_string(port).c_str());
  std::vector<GameInfoDto> games = lobby.get_games();

  std::vector<char> gamename(10); // hardcodeado
  lobby.send_selected_game(gamename);

  Socket skt = lobby.transfer_socket();
  int client_id = 1;
  Renderer renderer(client_id, skt);
  renderer.run();

  return exitCode;
}
