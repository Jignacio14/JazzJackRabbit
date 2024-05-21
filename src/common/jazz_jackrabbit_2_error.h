#include <cstdint>
#include <stdexcept>
#include <string>

class JazzJackrabbit2Error : public std::exception {
private:
  // cppcheck-suppress unusedStructMember
  const std::string base_message;
  // cppcheck-suppress unusedStructMember
  const int32_t line_number;
  // cppcheck-suppress unusedStructMember
  const std::string module;
  // cppcheck-suppress unusedStructMember
  std::string final_message;

public:
  /*
   *   Custom exception created to be used throught the game, both in the server
   * and in the client. It's an upgrade from a regular std::exception because it
   * carries the line number
   * (__LINE__) and module name  (__FILE__) where the exception was thrown, this
   * has to be filled at the time of instantiation by the caller
   */
  JazzJackrabbit2Error(const std::string &base_message,
                       const int32_t &line_number, const std::string &module);

  const char *what() const noexcept;
};
