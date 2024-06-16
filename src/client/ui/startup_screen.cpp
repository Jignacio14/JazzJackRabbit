#include "startup_screen.h"
#include "../../data/convention.h"
#include <iostream>

const static int EXIT_SUCCESS_CODE = 0;
const static int EXIT_ERROR_CODE = -1;

StartupScreen::StartupScreen(int &argc, char **argv, std::string &hostname,
                             uint32_t &port, std::string &username,
                             GameConfigs *game, Snapshot *initialSnapshot,
                             uint8_t &userCharacter)
    : app(argc, argv), hostname(hostname), port(port), username(username),
      game(game), initialSnapshot(initialSnapshot),
      userCharacter(userCharacter), lobby(nullptr),
      mainWindow(nullptr, hostname, port, username, this->game,
                 this->initialSnapshot, userCharacter, std::move(this->lobby)) {
}

const int StartupScreen::show() {
  this->mainWindow.show();
  const int mainWindowExitCode = this->app.exec();
  this->lobby = this->mainWindow.getLobby();

  if (mainWindowExitCode != EXIT_SUCCESS_CODE) {
    const std::string errorMessage =
        "Error while closing StartupScreen. Shutting down.";
    std::cerr << errorMessage << std::endl;

    if (this->lobby) {
      this->lobby->quit_game();
    }

    return EXIT_ERROR_CODE;
  }

  if (this->game->getOwnerName().empty()) {
    const std::string errorMessage = "After closing StartupScreen no game "
                                     "configs loaded correctly. Shutting down.";
    std::cerr << errorMessage << std::endl;

    if (this->lobby) {
      this->lobby->quit_game();
    }

    return EXIT_ERROR_CODE;
  }

  if (this->userCharacter == PlayableCharactersIds::NoneSelected) {
    const std::string errorMessage =
        "After closing StartupScreen no character selected. Shutting down.";
    std::cerr << errorMessage << std::endl;

    if (this->lobby) {
      this->lobby->quit_game();
    }

    return EXIT_ERROR_CODE;
  }

  if (this->lobby == nullptr) {
    const std::string errorMessage =
        "After closing StartupScreen no connection established. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  return mainWindowExitCode;
}

std::unique_ptr<Lobby> StartupScreen::getLobby() {
  std::unique_ptr<Lobby> tempLobby = std::move(this->lobby);
  this->lobby = nullptr;
  return tempLobby;
}
