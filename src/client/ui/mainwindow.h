#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdint>
#include <memory>
#include <qlineedit.h>
#include <qmediaplayer.h>
#include <qmediaplaylist.h>
#include <qmovie.h>
#include <qpushbutton.h>
#include <qsound.h>
#include <qstring.h>
#include <qthread.h>
#include <string>
#include <thread>

#include "../../data/snapshot_dto.h"
#include "../game_configs.h"
#include "../lobby.h"

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
  void on_maxPlayersInput_textChanged(const QString &newString);

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

  void on_carrotusScenarioRadioButton_released();
  void on_beachWorldScenarioRadioButton_released();

  void startGame();
  void joinGame(const GameConfigs &game);

private:
  // cppcheck-suppress unusedStructMember
  Ui::MainWindow *ui;

  std::string &hostname;
  uint32_t &port;
  std::string &username;
  GameConfigs *finalGameConfigs;
  Snapshot *initialSnapshot;
  std::string gameOwnerName;
  uint32_t gameDuration;
  uint32_t maxPlayers;
  uint32_t currentPlayers;
  uint8_t &characterSelected;
  uint8_t &scenarioSelected;

  QSound buttonClickSound;
  QMovie jazzAnimation;
  QMovie spazAnimation;
  QMovie loriAnimation;

  uint32_t debug_counter;
  std::vector<GameConfigs> latestGames;
  bool lobbyMoved;
  std::unique_ptr<Lobby> lobby;

  std::unique_ptr<std::thread> waitingPlayersAndStartTask;

  QMediaPlayer mediaPlayer;
  QMediaPlaylist mediaPlaylist;

  void enableButton(QPushButton *button, const std::string &id);

  void changeLineEditStyleBasedOnItsText(const QString &string,
                                         QLineEdit *lineEdit,
                                         const std::string &lineEditId,
                                         const uint32_t &marginRight);

  void disableLineEdit(QLineEdit *lineEdit, const std::string &lineEditId);

  void enableAndResetLineEdit(QLineEdit *lineEdit,
                              const std::string &lineEditId);

  void showTooltip(QPoint &location, QString &message);

  const bool isHostnameValid(std::string &message);

  const bool isPortValid(std::string &message);

  const bool isUsernameValid(std::string &message);

  const bool isGameDurationValid(std::string &message);

  const bool isNumberOfPlayersValid(std::string &message);

  std::vector<GameConfigs> getGamesFromServer();

  std::vector<GameConfigs> getRefreshedGamesFromServer();

  void addGamesToList(std::vector<GameConfigs> &games);

  QWidget *createGameItemWidget(const GameConfigs &game);

  void waitForPlayers();

public:
  MainWindow(QWidget *parent, std::string &hostname, uint32_t &port,
             std::string &username, GameConfigs *game,
             Snapshot *initialSnapshot, uint8_t &userCharacter,
             uint8_t &scenarioSelected, std::unique_ptr<Lobby> lobby);

  std::unique_ptr<Lobby> getLobby();

  void playMusic();

  void stopMusic();

  ~MainWindow();
};
#endif // MAINWINDOW_H
