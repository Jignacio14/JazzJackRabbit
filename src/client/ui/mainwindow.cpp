#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qfontdatabase.h>
#include <qstring.h>

const static int SCREEN_SIZE_X = 800;
const static int SCREEN_SIZE_Y = 600;
const static char JOYSTIX_RESOURCE_FONT_PATH[] = ":/fonts/assets/Joystix.otf";
const static char BUTTON_CLICK_RESOURCE_SOUND_PATH[] =
    ":/sounds/assets/button_click.wav";

MainWindow::MainWindow(QWidget *parent, std::string &hostname,
                       std::string &port)
    : QMainWindow(parent), ui(new Ui::MainWindow), hostname(hostname),
      port(port), buttonClickSound(BUTTON_CLICK_RESOURCE_SOUND_PATH) {
  ui->setupUi(this);
  QFontDatabase::addApplicationFont(JOYSTIX_RESOURCE_FONT_PATH);
  this->setFixedSize(QSize(SCREEN_SIZE_X, SCREEN_SIZE_Y));
  this->ui->hostnameInput->setFocus();
}

void MainWindow::on_hostnameInput_textChanged(const QString &newString) {
  this->hostname = newString.toStdString();

  if (newString.toStdString().empty()) {
    this->ui->hostnameInput->setStyleSheet(
        "QLineEdit#hostnameInput {  background-color: rgb(255, 255, 255);  "
        "color: rgba(99, 99, 99, 200);  font-family: Joystix;  border-radius: "
        "3px;  margin-left: 15px;  margin-right: 30px; }");
  } else {
    this->ui->hostnameInput->setStyleSheet(
        "QLineEdit#hostnameInput {  background-color: rgb(255, 255, 255);  "
        "color: rgb(0, 0, 0);  font-family: Joystix;  border-radius: 3px;  "
        "margin-left: 15px;  margin-right: 30px; }");
  }
}

void MainWindow::on_portInput_textChanged(const QString &newString) {
  this->port = newString.toStdString();

  if (newString.toStdString().empty()) {
    this->ui->portInput->setStyleSheet(
        "QLineEdit#portInput {  background-color: rgb(255, 255, 255);  "
        "color: rgba(99, 99, 99, 200);  font-family: Joystix;  border-radius: "
        "3px;  margin-left: 15px;  margin-right: 30px; }");
  } else {
    this->ui->portInput->setStyleSheet(
        "QLineEdit#portInput {  background-color: rgb(255, 255, 255);  "
        "color: rgb(0, 0, 0);  font-family: Joystix;  border-radius: 3px;  "
        "margin-left: 15px;  margin-right: 30px; }");
  }
}

void MainWindow::on_connectButton_pressed() {
  this->buttonClickSound.play();

  // if connection sucessful
  this->enableButton(this->ui->createGameButton, "createGameButton");
  this->enableButton(this->ui->joinGameButton, "joinGameButton");
}

void MainWindow::enableButton(QPushButton *button, const std::string &id) {
  std::string enabledStylesheet =
      "QPushButton#" + id +
      " {  background-color: rgba(177,252,3,140);  "
      "color: rgb(255, 255, 255);  border-radius: 18px;  font-family: Joystix; "
      "}  QPushButton#" +
      id + ":hover, QPushButton#" + id +
      ":focus {  "
      "background-color: rgba(177,252,3,180);  color: rgb(255, 255, 255); }  "
      "QPushButton#" +
      id +
      ":pressed {  background-color: "
      "rgba(177,252,3,160);  color: rgb(255, 255, 255);  padding-left: 3px;  "
      "padding-top: 3px; }";

  button->setEnabled(true);
  button->setStyleSheet(QString(enabledStylesheet.c_str()));
}

void MainWindow::on_createGameButton_pressed() {
  this->buttonClickSound.play();
  this->ui->stackedWidget->setCurrentWidget(this->ui->page_2);
}

void MainWindow::on_joinGameButton_pressed() { this->buttonClickSound.play(); }

void MainWindow::on_quitButton_pressed() { this->buttonClickSound.play(); }

void MainWindow::on_quitButton_released() { this->close(); }

MainWindow::~MainWindow() { delete ui; }
