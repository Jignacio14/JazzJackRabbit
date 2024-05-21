#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
  // cppcheck-suppress unusedStructMember
  Ui::MainWindow *ui;
  std::string &hostname;
  std::string &port;

public:
  MainWindow(QWidget *parent, std::string &hostname, std::string &port);
  ~MainWindow();
};
#endif // MAINWINDOW_H
