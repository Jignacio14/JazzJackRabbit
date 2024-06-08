#ifndef STARTUP_SCREEN_H
#define STARTUP_SCREEN_H

#include "../../common/snapshot_DTO.h"
#include "../lobby.h"
#include "mainwindow.h"
#include <QApplication>
#include <cstdint>
#include <memory>
#include <string>

class StartupScreen {
private:
  QApplication app;
  std::string &hostname;
  uint32_t &port;
  std::string &username;
  GameConfigs *game;
  Snapshot *initialSnapshot;
  char &userCharacter;
  std::unique_ptr<Lobby> lobby;

  MainWindow mainWindow;

public:
  StartupScreen(int &argc, char **argv, std::string &hostname, uint32_t &port,
                std::string &username, GameConfigs *game,
                Snapshot *initialSnapshot, char &userCharacter);
  const int show();
  std::unique_ptr<Lobby> getLobby();
};

#endif // STARTUP_SCREEN_H
