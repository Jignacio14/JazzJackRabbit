#ifndef STARTUP_SCREEN_H
#define STARTUP_SCREEN_H

#include "mainwindow.h"
#include <QApplication>
#include <string>

class StartupScreen {
private:
  QApplication app;
  std::string &hostname;
  std::string &port;
  MainWindow mainWindow;

public:
  StartupScreen(int &argc, char **argv, std::string &hostname,
                std::string &port);
  const int show();
};

#endif // STARTUP_SCREEN_H
