#include "./server.h"
#include <exception>
#include <iostream>
#include <ostream>

const static int EXIT_SUCCESS_CODE = 0;
const static int EXIT_ERROR_CODE = -1;

int main(int argc, const char *argv[]) {
  const uint8_t EXPECTED_ARGUMENTS = 2;

  try {

    if (argc != EXPECTED_ARGUMENTS) {
      const std::string errorMessage =
          "Error while calling program. Expected " + std::string(argv[0]) +
          "<port> call with no extra arguments";
      std::cerr << errorMessage << std::endl;
      return EXIT_ERROR_CODE;
    }

    std::string port = argv[1];
    Server server(port);
    server.run();

    return EXIT_SUCCESS_CODE;
  } catch (const std::exception &error) {
    std::cerr << "\nException thrown and caught:\n"
              << error.what() << std::endl;
    return EXIT_ERROR_CODE;

  } catch (...) {
    std::cerr << "\nUnknown exception caught.\n" << std::endl;
    return EXIT_ERROR_CODE;
  }
}
