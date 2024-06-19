#include "../data/convention.h"
#include "../data/snapshot_dto.h"
#include "./game_configs.h"
#include "./graphics/graphic_engine.h"
#include "./player.h"
#include "./sound/audio_engine.h"
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

void debugPrint(std::string &hostname, uint32_t &port, std::string &username,
                uint8_t &userCharacter, GameConfigs &gameConfig) {
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
  uint32_t port(0);
  std::string username("");
  uint8_t userCharacter = PlayableCharactersIds::NoneSelected;
  uint8_t scenarioSelected = ScenariosIds::Carrotus;

  Snapshot initialSnapshotDto;
  Snapshot *initialSnapshotDtoPtr = &initialSnapshotDto;

  GameConfigs gameConfig;
  GameConfigs *gamePtr = &gameConfig;

  std::unique_ptr<Lobby> lobby = nullptr;

  int exitCode = 0;

  try {

    StartupScreen startupScreen(argc, argv, hostname, port, username, gamePtr,
                                initialSnapshotDtoPtr, userCharacter,
                                scenarioSelected);

    exitCode = startupScreen.show();
    lobby = startupScreen.getLobby();

    if (exitCode != EXIT_SUCCESS_CODE) {
      return EXIT_ERROR_CODE;
    }

    GraphicEngine graphicEngine;
    graphicEngine.preloadTextures();

    AudioEngine audioEngine;
    audioEngine.preloadAudios();

    SnapshotWrapper initialSnapshot(initialSnapshotDto);

    uint8_t playerId = lobby->get_player_id();
    Player player(username, userCharacter, graphicEngine, audioEngine,
                  initialSnapshot, playerId);
    Socket skt = lobby->transfer_socket();
    Renderer renderer(graphicEngine, audioEngine, playerId, std::move(skt),
                      player, initialSnapshot, scenarioSelected);
    renderer.run();

    graphicEngine.closeWindow();

    return exitCode;

  } catch (const std::exception &error) {
    std::cerr << "\nException thrown and caught:\n"
              << error.what() << std::endl;
    return EXIT_ERROR_CODE;

  } catch (...) {
    std::cerr << "\nUnknown exception caught.\n" << std::endl;
    return EXIT_ERROR_CODE;
  }
}
