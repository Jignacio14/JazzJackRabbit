#include <cstdint>
#include <stdexcept>
#include <string>

class DisconnectionException : public std::exception {
private:
  // cppcheck-suppress unusedStructMember
  std::string message;
  // cppcheck-suppress unusedStructMember
  const int32_t line_number;
  // cppcheck-suppress unusedStructMember
  const std::string module;

public:
  DisconnectionException(const int32_t &line_number, const std::string &module);

  const char *what() const noexcept;
};
