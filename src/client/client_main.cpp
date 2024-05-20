#include "./ui/startup_screen.h"
#include <iostream>

int main(int argc, char *argv[]) {
  StartupScreen startupScreen(argc, argv);
  const int exitCodeStartupScreen = startupScreen.show();
  std::cout << "Client exit: " << exitCodeStartupScreen << std::endl;
  return exitCodeStartupScreen;
}
