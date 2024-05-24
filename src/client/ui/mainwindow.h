#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdint>
#include <qlineedit.h>
#include <qmovie.h>
#include <qpushbutton.h>
#include <qsound.h>
#include <qstring.h>
#include <string>

#include "../game_configs.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  // cppcheck-suppress unknownMacro
private slots:
  void on_hostnameInput_textChanged(const QString &newString);
  void on_portInput_textChanged(const QString &newString);
  void on_usernameInput_textChanged(const QString &newString);
  void on_gameDurationInput_textChanged(const QString &newString);
  void on_numberOfPlayersInput_textChanged(const QString &newString);

  void on_connectButton_released();

  void on_createGameButton_pressed();
  void on_joinGameButton_pressed();
  void on_quitButton_pressed();
  void on_quitButton_released();

  void on_chooseCharacterButton_pressed();
  void on_chooseCharacterButton_released();

  void on_selectJazzButton_released();
  void on_selectSpazButton_released();
  void on_selectLoriButton_released();

  void on_refreshGamesButton_released();

  void on_backInCreateGameButton_released();
  void on_backInJoinGameButton_released();
  void on_backInChooseCharacterButton_released();

  void startGame();

private:
  // cppcheck-suppress unusedStructMember
  Ui::MainWindow *ui;

  std::string &hostname;
  uint32_t &port;
  std::string username;
  uint32_t gameDuration;
  uint32_t numberOfPlayers;
  char characterSelected;

  QSound buttonClickSound;
  QMovie jazzAnimation;
  QMovie spazAnimation;
  QMovie loriAnimation;

  uint32_t debug_counter;
  std::vector<GameConfigs> latestGames;

  void enableButton(QPushButton *button, const std::string &id);

  void changeLineEditStyleBasedOnItsText(const QString &string,
                                         QLineEdit *lineEdit,
                                         const std::string &lineEditId,
                                         const uint32_t &marginRight);

  void showTooltip(QPoint &location, QString &message);

  const bool isHostnameValid(std::string &message);

  const bool isPortValid(std::string &message);

  const bool isUsernameValid(std::string &message);

  const bool isGameDurationValid(std::string &message);

  const bool isNumberOfPlayersValid(std::string &message);

  std::vector<GameConfigs> getGamesFromServer();

  void addGamesToList(std::vector<GameConfigs> &games);

  QWidget *createGameItemWidget(const GameConfigs &game);

public:
  MainWindow(QWidget *parent, std::string &hostname, uint32_t &port);

  ~MainWindow();
};
#endif // MAINWINDOW_H
