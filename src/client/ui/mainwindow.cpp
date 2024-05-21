#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qfontdatabase.h>

const static int SCREEN_SIZE_X = 800;
const static int SCREEN_SIZE_Y = 600;
const static char JOYSTIX_RESOURCE_FONT_PATH[] = ":/fonts/assets/Joystix.otf";

MainWindow::MainWindow(QWidget *parent, std::string &hostname,
                       std::string &port)
    : QMainWindow(parent), ui(new Ui::MainWindow), hostname(hostname),
      port(port) {
  ui->setupUi(this);
  QFontDatabase::addApplicationFont(JOYSTIX_RESOURCE_FONT_PATH);
  this->setFixedSize(QSize(SCREEN_SIZE_X, SCREEN_SIZE_Y));
}

void MainWindow::on_hostnameInput_textChanged(const QString &newString) {
  this->hostname = newString.toStdString();
}

void MainWindow::on_portInput_textChanged(const QString &newString) {
  this->port = newString.toStdString();
}

MainWindow::~MainWindow() { delete ui; }
