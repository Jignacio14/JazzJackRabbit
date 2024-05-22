#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <qsound.h>
#include <string>

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

  void on_connectButton_pressed();
  void on_createGameButton_pressed();
  void on_joinGameButton_pressed();
  void on_quitButton_pressed();
  void on_quitButton_released();

private:
  // cppcheck-suppress unusedStructMember
  Ui::MainWindow *ui;
  std::string &hostname;
  std::string &port;
  QSound buttonClickSound;

  void enableButton(QPushButton *button, const std::string &id);

public:
  MainWindow(QWidget *parent, std::string &hostname, std::string &port);
  ~MainWindow();
};
#endif // MAINWINDOW_H
