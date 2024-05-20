#ifndef STARTUP_SCREEN_H
#define STARTUP_SCREEN_H

#include "mainwindow.h"
#include <QApplication>

class StartupScreen {
private:
  QApplication app;
  MainWindow mainWindow;

public:
  StartupScreen(int &argc, char **argv);
  const int show();
};

#endif // STARTUP_SCREEN_H
