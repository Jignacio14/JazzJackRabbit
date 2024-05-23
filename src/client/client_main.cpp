#include "./ui/startup_screen.h"
#include <cstdint>
#include <iostream>
#include <string>

const static int EXIT_SUCCESS_CODE = 0;
const static int EXIT_ERROR_CODE = -1;

int main(int argc, char *argv[]) {
  const uint8_t EXPECTED_ARGUMENTS = 1;

  if (argc != EXPECTED_ARGUMENTS) {
    const std::string errorMessage = "Error while calling program. Expected " +
                                     std::string(argv[0]) +
                                     "call with no extra arguments";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  std::string hostname("");
  uint32_t port(0);

  StartupScreen startupScreen(argc, argv, hostname, port);

  int exitCode = startupScreen.show();

  if (exitCode != EXIT_SUCCESS_CODE) {
    const std::string errorMessage =
        "Error while closing StartupScreen. Shutting down.";
    std::cerr << errorMessage << std::endl;
    return EXIT_ERROR_CODE;
  }

  std::cout << hostname << ":" << port << std::endl;

  return exitCode;
}
