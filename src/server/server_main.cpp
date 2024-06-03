#include "./server.h"
#include <exception>
#include <iostream>
#include <ostream>

int main(int argc, const char *argv[]) {
  try {
    if (argc != 2) {
      std::cout << "Arg number error, expected 2 but got " << argc
                << "\nExiting..." << std::endl;
      return -1;
    }
    std::string port = argv[1];
    Server server(port);
    server.execute();
    return 0;
  } catch (const std::exception &exception) {
    std::cout << "An unexpected error has ocurred" << std::endl;
    return -1;
  }
}
