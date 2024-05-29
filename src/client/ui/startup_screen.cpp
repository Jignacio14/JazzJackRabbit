#include "startup_screen.h"

StartupScreen::StartupScreen(int &argc, char **argv, std::string &hostname,
                             uint32_t &port, std::string &username,
                             GameConfigs **game, char &userCharacter)
    : app(argc, argv), hostname(hostname), port(port), username(username),
      game(game), userCharacter(userCharacter),
      mainWindow(nullptr, hostname, port, username, this->game, userCharacter) {
}

const int StartupScreen::show() {
  this->mainWindow.show();
  const int mainWindowExitCode = this->app.exec();

  return mainWindowExitCode;
}
