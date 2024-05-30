#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qfontdatabase.h>
#include <qlabel.h>
#include <qobject.h>
#include <qstring.h>
#include <qtimer.h>
#include <qtooltip.h>

#include "../../common/random_string_generator.h"

const static int SCREEN_SIZE_X = 800;
const static int SCREEN_SIZE_Y = 600;
const static char JOYSTIX_RESOURCE_FONT_PATH[] = ":/fonts/assets/Joystix.otf";
const static char BUTTON_CLICK_RESOURCE_SOUND_PATH[] =
    ":/sounds/assets/button_click.wav";
const static char JAZZ_MENU_ANIMATION_RESOURCE_PATH[] =
    ":/animations/assets/jazz_menu_animation.gif";
const static char SPAZ_MENU_ANIMATION_RESOURCE_PATH[] =
    ":/animations/assets/spaz_menu_animation.gif";
const static char LORI_MENU_ANIMATION_RESOURCE_PATH[] =
    ":/animations/assets/lori_menu_animation.gif";
const static int TIME_FOR_CHARACTER_ANIMATION_WAIT = 1000; // In ms

const static uint32_t MAX_USERNAME_SIZE = 32;
const static uint32_t MAX_PORT_NUMBER = 65535;
const static uint32_t MIN_NUMBER_OF_PLAYERS = 1;

const static char CHARACTER_NOT_SELECTED = '0';
const static char JAZZ_SELECTED = 'J';
const static char SPAZ_SELECTED = 'S';
const static char LORI_SELECTED = 'L';

MainWindow::MainWindow(QWidget *parent, std::string &hostname, uint32_t &port,
                       std::string &username, GameConfigs *game,
                       char &userCharacter)
    : QMainWindow(parent), ui(new Ui::MainWindow), hostname(hostname),
      port(port), username(username), finalGameConfigs(game), gameOwnerName(""),
      gameDuration(0), maxPlayers(0), currentPlayers(1),
      characterSelected(userCharacter),
      buttonClickSound(BUTTON_CLICK_RESOURCE_SOUND_PATH),
      jazzAnimation(JAZZ_MENU_ANIMATION_RESOURCE_PATH),
      spazAnimation(SPAZ_MENU_ANIMATION_RESOURCE_PATH),
      loriAnimation(LORI_MENU_ANIMATION_RESOURCE_PATH), debug_counter(0) {

  // Qt setup and set screen size
  this->ui->setupUi(this);
  this->setFixedSize(QSize(SCREEN_SIZE_X, SCREEN_SIZE_Y));

  // Add font from resource file
  QFontDatabase::addApplicationFont(JOYSTIX_RESOURCE_FONT_PATH);

  // Set the proper screen for startup
  this->ui->stackedWidget->setCurrentWidget(this->ui->initialScreen);
  this->ui->hostnameInput->setFocus();

  // Character animations initialization
  this->ui->selectJazzLabel->setMovie(&this->jazzAnimation);
  this->jazzAnimation.start();
  this->jazzAnimation.stop();

  this->ui->selectSpazLabel->setMovie(&this->spazAnimation);
  this->spazAnimation.start();
  this->spazAnimation.stop();

  this->ui->selectLoriLabel->setMovie(&this->loriAnimation);
  this->loriAnimation.start();
  this->loriAnimation.stop();
}

void MainWindow::on_hostnameInput_textChanged(const QString &newString) {
  this->hostname = newString.toStdString();
  const uint32_t marginRight = 30;
  changeLineEditStyleBasedOnItsText(newString, this->ui->hostnameInput,
                                    "hostnameInput", marginRight);
}

void MainWindow::on_portInput_textChanged(const QString &newString) {
  this->port = newString.toUInt();
  const uint32_t marginRight = 30;
  changeLineEditStyleBasedOnItsText(newString, this->ui->portInput, "portInput",
                                    marginRight);
}

void MainWindow::on_usernameInput_textChanged(const QString &newString) {
  this->username = newString.toStdString();
  const uint32_t marginRight = 15;
  changeLineEditStyleBasedOnItsText(newString, this->ui->usernameInput,
                                    "usernameInput", marginRight);
}

void MainWindow::on_gameDurationInput_textChanged(const QString &newString) {
  this->gameDuration = newString.toUInt();
  const uint32_t marginRight = 15;
  changeLineEditStyleBasedOnItsText(newString, this->ui->gameDurationInput,
                                    "gameDurationInput", marginRight);
}

void MainWindow::on_maxPlayersInput_textChanged(const QString &newString) {
  this->maxPlayers = newString.toUInt();
  const uint32_t marginRight = 15;
  changeLineEditStyleBasedOnItsText(newString, this->ui->maxPlayersInput,
                                    "maxPlayersInput", marginRight);
}

void MainWindow::on_connectButton_released() {
  this->buttonClickSound.play();

  std::string tooltipMessage("");
  QString qTooltipMessage;
  QPoint location;

  // Input validation

  if (!this->isHostnameValid(tooltipMessage)) {
    location = this->ui->hostnameInput->mapToGlobal(QPoint(10, -40));
    qTooltipMessage = QString::fromStdString(tooltipMessage);
    this->showTooltip(location, qTooltipMessage);
    return;
  }

  if (!this->isPortValid(tooltipMessage)) {
    location = this->ui->portInput->mapToGlobal(QPoint(10, -40));
    qTooltipMessage = QString::fromStdString(tooltipMessage);
    this->showTooltip(location, qTooltipMessage);
    return;
  }

  // if connection sucessful then enable buttons
  this->enableButton(this->ui->createGameButton, "createGameButton");
  this->enableButton(this->ui->joinGameButton, "joinGameButton");
}

void MainWindow::on_createGameButton_pressed() {
  this->buttonClickSound.play();
  this->enableAndResetLineEdit(this->ui->usernameInput, "usernameInput");
  this->enableAndResetLineEdit(this->ui->gameDurationInput,
                               "gameDurationInput");
  this->enableAndResetLineEdit(this->ui->maxPlayersInput, "maxPlayersInput");
  this->ui->stackedWidget->setCurrentWidget(this->ui->createGameScreen);
}

void MainWindow::on_joinGameButton_pressed() {
  this->buttonClickSound.play();

  std::vector<GameConfigs> games = this->getGamesFromServer();
  this->addGamesToList(games);

  this->ui->stackedWidget->setCurrentWidget(this->ui->joinGameScreen);
}

void MainWindow::on_quitButton_pressed() { this->buttonClickSound.play(); }

void MainWindow::on_quitButton_released() { this->close(); }

void MainWindow::on_chooseCharacterButton_pressed() {
  this->buttonClickSound.play();
}

void MainWindow::on_chooseCharacterButton_released() {
  std::string tooltipMessage("");
  QString qTooltipMessage;
  QPoint location;

  // Input validation

  if (!this->isUsernameValid(tooltipMessage)) {
    location = this->ui->usernameInput->mapToGlobal(QPoint(10, -40));
    qTooltipMessage = QString::fromStdString(tooltipMessage);
    this->showTooltip(location, qTooltipMessage);
    return;
  }

  if (!this->isGameDurationValid(tooltipMessage)) {
    location = this->ui->gameDurationInput->mapToGlobal(QPoint(10, -40));
    qTooltipMessage = QString::fromStdString(tooltipMessage);
    this->showTooltip(location, qTooltipMessage);
    return;
  }

  if (!this->isNumberOfPlayersValid(tooltipMessage)) {
    location = this->ui->maxPlayersInput->mapToGlobal(QPoint(10, -40));
    qTooltipMessage = QString::fromStdString(tooltipMessage);
    this->showTooltip(location, qTooltipMessage);
    return;
  }

  if (this->gameOwnerName.empty()) {
    this->gameOwnerName = this->username;
  }

  this->ui->stackedWidget->setCurrentWidget(this->ui->chooseCharacterScreen);
}

void MainWindow::on_selectJazzButton_released() {
  this->buttonClickSound.play();
  this->characterSelected = JAZZ_SELECTED;
  this->jazzAnimation.start();
  QTimer::singleShot(TIME_FOR_CHARACTER_ANIMATION_WAIT, this,
                     SLOT(startGame()));
}

void MainWindow::on_selectSpazButton_released() {
  this->buttonClickSound.play();
  this->characterSelected = SPAZ_SELECTED;
  this->spazAnimation.start();
  QTimer::singleShot(TIME_FOR_CHARACTER_ANIMATION_WAIT, this,
                     SLOT(startGame()));
}

void MainWindow::on_selectLoriButton_released() {
  this->buttonClickSound.play();
  this->characterSelected = LORI_SELECTED;
  this->loriAnimation.start();
  QTimer::singleShot(TIME_FOR_CHARACTER_ANIMATION_WAIT, this,
                     SLOT(startGame()));
}

void MainWindow::on_refreshGamesButton_released() {
  this->buttonClickSound.play();
  std::vector<GameConfigs> games = this->getGamesFromServer();

  this->addGamesToList(games);

  this->ui->stackedWidget->setCurrentWidget(this->ui->joinGameScreen);
}

void MainWindow::on_backInCreateGameButton_released() {
  this->buttonClickSound.play();
  this->gameOwnerName = "";
  this->ui->stackedWidget->setCurrentWidget(this->ui->initialScreen);
}

void MainWindow::on_backInJoinGameButton_released() {
  this->buttonClickSound.play();
  this->gameOwnerName = "";
  this->ui->stackedWidget->setCurrentWidget(this->ui->initialScreen);
}

void MainWindow::on_backInChooseCharacterButton_released() {
  this->buttonClickSound.play();
  this->ui->stackedWidget->setCurrentWidget(this->ui->createGameScreen);
}

void MainWindow::startGame() {
  this->ui->stackedWidget->setCurrentWidget(this->ui->waitingToJoinScreen);

  std::string remainingPlayers = std::to_string(this->currentPlayers) + "/" +
                                 std::to_string(this->maxPlayers);
  this->ui->waitingOthersCounterLabel->setText(
      QString::fromStdString(remainingPlayers));

  *this->finalGameConfigs =
      GameConfigs(this->gameOwnerName, this->maxPlayers, this->currentPlayers,
                  this->gameDuration);
  std::cout << "Game starting!"
            << "\n";
  this->close();
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

void MainWindow::changeLineEditStyleBasedOnItsText(
    const QString &string, QLineEdit *lineEdit, const std::string &lineEditId,
    const uint32_t &marginRight) {

  if (string.toStdString().empty()) {
    std::string emptyLineEditStyle =
        "QLineEdit#" + lineEditId +
        " {  background-color: rgb(255, 255, 255);  "
        "color: rgba(99, 99, 99, 200);  font-family: Joystix;  border-radius: "
        "3px;  margin-left: 15px;  margin-right: " +
        std::to_string(marginRight) + "px; }";
    lineEdit->setStyleSheet(QString::fromStdString(emptyLineEditStyle));

  } else {
    std::string lineEditHasTextStyle =
        "QLineEdit#" + lineEditId +
        " {  background-color: rgb(255, 255, 255);  "
        "color: rgb(0, 0, 0);  font-family: Joystix;  border-radius: 3px;  "
        "margin-left: 15px;  margin-right: " +
        std::to_string(marginRight) + "px; }";
    lineEdit->setStyleSheet(QString::fromStdString(lineEditHasTextStyle));
  }
}

void MainWindow::disableLineEdit(QLineEdit *lineEdit,
                                 const std::string &lineEditId) {

  std::string emptyLineEditStyle =
      "QLineEdit#" + lineEditId +
      " {  background-color: rgb(181, 181, 181);  "
      "color: rgb(0, 0, 0); font-family: Joystix; margin-left: 15px; "
      "margin-right: 15px; border-radius: "
      "15px; }";
  lineEdit->setStyleSheet(QString::fromStdString(emptyLineEditStyle));
  lineEdit->setEnabled(false);
}

void MainWindow::enableAndResetLineEdit(QLineEdit *lineEdit,
                                        const std::string &lineEditId) {

  lineEdit->setEnabled(true);
  lineEdit->clear();
  uint32_t rightMargin = 15;
  this->changeLineEditStyleBasedOnItsText(lineEdit->text(), lineEdit,
                                          lineEditId, rightMargin);
}

void MainWindow::showTooltip(QPoint &location, QString &message) {
  QToolTip::showText(location, message);
}

const bool MainWindow::isHostnameValid(std::string &message) {
  if (this->hostname.empty()) {
    message = "Hostname cannot be empty";
    return false;
  }

  return true;
}

const bool MainWindow::isPortValid(std::string &message) {
  if (this->port == 0) {
    message = "Port must be filled with a number greater than zero";
    return false;
  }

  if (this->port >= MAX_PORT_NUMBER) {
    message = "Port cannot be greater than " + std::to_string(MAX_PORT_NUMBER);
    return false;
  }

  return true;
}

const bool MainWindow::isUsernameValid(std::string &message) {
  if (this->username.empty()) {
    message = "Username cannot be empty";
    return false;
  }

  if (this->username.size() >= MAX_USERNAME_SIZE) {
    message = "Username must be " + std::to_string(MAX_USERNAME_SIZE) +
              " characters or less";
    return false;
  }

  return true;
}

const bool MainWindow::isGameDurationValid(std::string &message) {
  if (this->gameDuration == 0) {
    message = "Game duration must be filled with a number greater than zero";
    return false;
  }

  return true;
}

const bool MainWindow::isNumberOfPlayersValid(std::string &message) {
  if (this->maxPlayers < MIN_NUMBER_OF_PLAYERS) {
    message = "Number of players must be filled with a number greater than one";
    return false;
  }

  return true;
}

std::vector<GameConfigs> MainWindow::getGamesFromServer() {
  std::vector<GameConfigs> games;
  for (int i = 0; i < 19; i++) {
    uint32_t userId = i + this->debug_counter;
    games.push_back(GameConfigs("user_" + std::to_string(userId), 3, 2, 120));
    this->debug_counter++;
  }

  return games;
}

void MainWindow::addGamesToList(std::vector<GameConfigs> &games) {
  this->ui->gamesList->clear();
  this->latestGames.clear();
  this->latestGames = games;

  for (const auto &game : latestGames) {
    QListWidgetItem *listWidgetItem = new QListWidgetItem(this->ui->gamesList);
    QWidget *itemWidget = this->createGameItemWidget(game);
    listWidgetItem->setSizeHint(itemWidget->sizeHint());
    this->ui->gamesList->setItemWidget(listWidgetItem, itemWidget);
  }
}

void MainWindow::joinGame(const GameConfigs &game) {
  this->gameDuration = game.getGameDuration();
  this->maxPlayers = game.getMaxNumberOfPlayers();
  this->currentPlayers =
      game.getCurrentNumberOfPlayers() + 1; // +1 Because this client joined
  this->gameOwnerName = game.getOwnerName();
  this->ui->stackedWidget->setCurrentWidget(this->ui->createGameScreen);

  this->enableAndResetLineEdit(this->ui->usernameInput, "usernameInput");

  this->ui->gameDurationInput->setText(
      QString::fromStdString(std::to_string(this->gameDuration)));
  this->disableLineEdit(this->ui->gameDurationInput, "gameDurationInput");

  this->ui->maxPlayersInput->setText(
      QString::fromStdString(std::to_string(this->maxPlayers)));
  this->disableLineEdit(this->ui->maxPlayersInput, "maxPlayersInput");
}

QWidget *MainWindow::createGameItemWidget(const GameConfigs &game) {
  QWidget *itemWidget = new QWidget(this);
  QHBoxLayout *layout = new QHBoxLayout(itemWidget);

  std::string parsedGameNameForButton =
      RandomStringGenerator::get_random_string() + "-button";
  std::string parsedGameNameForLabel =
      RandomStringGenerator::get_random_string() + "-label";
  QString qParsedGamedNameForButton =
      QString::fromStdString(parsedGameNameForButton);
  QString qParsedGamedNameForLabel =
      QString::fromStdString(parsedGameNameForLabel);

  QLabel *labelRoomName = new QLabel(
      QString::fromStdString(std::string(game.getOwnerName() + "'s room")));
  labelRoomName->setObjectName(qParsedGamedNameForLabel);

  QLabel *labelPlayers = new QLabel(QString::fromStdString(
      std::string(std::to_string(game.getCurrentNumberOfPlayers()) + "/" +
                  std::to_string(game.getMaxNumberOfPlayers()))));
  labelPlayers->setObjectName(qParsedGamedNameForLabel);

  QLabel *labelDuration = new QLabel(QString::fromStdString(
      std::string("  " + std::to_string(game.getGameDuration()) + "s")));
  labelDuration->setObjectName(qParsedGamedNameForLabel);

  QPushButton *button = new QPushButton("Join");
  button->setObjectName(qParsedGamedNameForButton);

  std::string buttonStylesheet =
      "QPushButton#" + parsedGameNameForButton +
      "{  background-color: rgba(177,252,3,140);  color: rgb(255, 255, 255);  "
      "border-radius: 5px;  font-family: Joystix; }  QPushButton#" +
      parsedGameNameForButton + ":hover, QPushButton#" +
      parsedGameNameForButton +
      ":focus {  background-color: rgba(177,252,3,180);  color: rgb(255, 255, "
      "255); }  QPushButton#" +
      parsedGameNameForButton +
      ":pressed {  background-color: rgba(177,252,3,160);  color: rgb(255, "
      "255, 255);  padding-left: 3px;  padding-top: 3px; }";

  std::string labelStylesheet =
      "QLabel#" + parsedGameNameForLabel +
      "{  color: rgb(255, 255, 255); font-family: Joystix; }";

  button->setStyleSheet(QString::fromStdString(buttonStylesheet));
  labelRoomName->setStyleSheet(QString::fromStdString(labelStylesheet));
  labelDuration->setStyleSheet(QString::fromStdString(labelStylesheet));
  labelPlayers->setStyleSheet(QString::fromStdString(labelStylesheet));

  QObject::connect(button, &QPushButton::clicked, [=]() {
    this->buttonClickSound.play();
    this->joinGame(game);
  });

  layout->addWidget(labelRoomName);
  layout->addWidget(labelDuration);
  layout->addWidget(labelPlayers);
  layout->addWidget(button);
  itemWidget->setLayout(layout);
  return itemWidget;
}

MainWindow::~MainWindow() { delete ui; }
