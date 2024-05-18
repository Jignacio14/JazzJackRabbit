#include "startup_screen.h"

StartupScreen::StartupScreen() : app() {}

void StartupScreen::show() {
  this->mainWindow.show();
  this->app.exec();
}
