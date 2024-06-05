#include "./game_configs.h"
#include "./graphics/graphic_engine.h"
#include "./ui/startup_screen.h"
#include "lobby.h"
#include "renderer.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <yaml-cpp/yaml.h>

#include "../common/global_configs.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

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
  std::unique_ptr<Lobby> lobby = nullptr;

  int exitCode = 0;

  if (TEST_ONLY_SDL_MODE == false) {
    StartupScreen startupScreen(argc, argv, hostname, port, username, gamePtr,
                                userCharacter);

    exitCode = startupScreen.show();
    lobby = startupScreen.getLobby();

    if (exitCode != EXIT_SUCCESS_CODE) {
      return EXIT_ERROR_CODE;
    }
  } else {
    hostname = globalConfigs.getDebugHostname();
    port = globalConfigs.getDebugPort();
    username = "testUsername";
    userCharacter = JAZZ_SELECTED;
    lobby =
        std::make_unique<Lobby>(hostname.c_str(), std::to_string(port).c_str());
  }

  GraphicEngine graphicEngine;
  graphicEngine.preloadTextures();

  debugPrint(hostname, port, username, userCharacter, gameConfig);

  int player_id = 1;
  Socket skt = lobby->transfer_socket();
  Renderer renderer(graphicEngine, player_id, std::move(skt));
  renderer.run();

  return exitCode;
}
