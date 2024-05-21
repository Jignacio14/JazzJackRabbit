#include "startup_screen.h"

StartupScreen::StartupScreen(int &argc, char **argv) : app(argc, argv) {}

const int StartupScreen::show() {
  this->mainWindow.show();
  const int mainWindowExitCode = this->app.exec();

  return mainWindowExitCode;
}
