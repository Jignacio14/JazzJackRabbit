#include "startup_screen.h"

StartupScreen::StartupScreen(int &argc, char **argv, std::string &hostname,
                             uint32_t &port)
    : app(argc, argv), hostname(hostname), port(port),
      mainWindow(nullptr, hostname, port) {}

const int StartupScreen::show() {
  this->mainWindow.show();
  const int mainWindowExitCode = this->app.exec();

  return mainWindowExitCode;
}
