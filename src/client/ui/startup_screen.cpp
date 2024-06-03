#include "startup_screen.h"
#include <iostream>

const static int EXIT_SUCCESS_CODE = 0;
const static int EXIT_ERROR_CODE = -1;
const static char CHARACTER_NOT_SELECTED = '0';

StartupScreen::StartupScreen(int &argc, char **argv, std::string &hostname,
                             uint32_t &port, std::string &username,
                             GameConfigs *game, char &userCharacter)
    : app(argc, argv), hostname(hostname), port(port), username(username),
      game(game), userCharacter(userCharacter),
      mainWindow(nullptr, hostname, port, username, this->game, userCharacter) {
}

const int StartupScreen::show() {
  this->mainWindow.show();
  const int mainWindowExitCode = this->app.exec();

  if (mainWindowExitCode != EXIT_SUCCESS_CODE) {
    const std::string errorMessage =
        "Error while closing StartupScreen. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  if (this->game->getOwnerName().empty()) {
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

  return mainWindowExitCode;
}
