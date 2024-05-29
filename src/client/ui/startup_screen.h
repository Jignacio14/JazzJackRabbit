#ifndef STARTUP_SCREEN_H
#define STARTUP_SCREEN_H

#include "mainwindow.h"
#include <QApplication>
#include <cstdint>
#include <string>

class StartupScreen {
private:
  QApplication app;
  std::string &hostname;
  uint32_t &port;
  std::string &username;
  GameConfigs **game;
  char &userCharacter;
  MainWindow mainWindow;

public:
  StartupScreen(int &argc, char **argv, std::string &hostname, uint32_t &port,
                std::string &username, GameConfigs **game, char &userCharacter);
  const int show();
};

#endif // STARTUP_SCREEN_H
