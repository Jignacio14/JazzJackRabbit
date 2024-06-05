#ifndef GLOBAL_CONFIGS_H
#define GLOBAL_CONFIGS_H

#include <cstdint>
#include <string>

class GlobalConfigs {
private:
  // cppcheck-suppress unusedStructMember
  uint16_t maxPlayersPerGame;
  // cppcheck-suppress unusedStructMember
  uint32_t maxGameDuration;
  // cppcheck-suppress unusedStructMember
  uint32_t maxUsernameLength;
  // cppcheck-suppress unusedStructMember
  uint32_t minNumberOfPlayers;
  // cppcheck-suppress unusedStructMember
  uint32_t maxPortNumber;
  // cppcheck-suppress unusedStructMember
  int screenSizeX;
  // cppcheck-suppress unusedStructMember
  int screenSizeY;
  // cppcheck-suppress unusedStructMember
  std::string windowName;
  // cppcheck-suppress unusedStructMember
  double targetFps;
  // cppcheck-suppress unusedStructMember
  std::string debugHostname;
  // cppcheck-suppress unusedStructMember
  uint32_t debugPort;

  GlobalConfigs();

  /*
   *  Delete copy constructor and copy assignment operator.
   */
  GlobalConfigs(const GlobalConfigs &) = delete;
  GlobalConfigs &operator=(const GlobalConfigs &) = delete;

  /*
   *  Delete move constructor and move assignment operator.
   */
  GlobalConfigs(const GlobalConfigs &&) = delete;
  GlobalConfigs &operator=(const GlobalConfigs &&) = delete;

public:
  /*
   *  Uses the Singleton design pattern
   *   Return the instance
   */
  static GlobalConfigs &getInstance();

  uint16_t getMaxPlayersPerGame() const;
  uint32_t getMaxGameDuration() const;
  uint32_t getMaxUsernameLength() const;
  uint32_t getMinNumberOfPlayers() const;
  uint32_t getMaxPortNumber() const;
  int getScreenSizeX() const;
  int getScreenSizeY() const;
  std::string getWindowName() const;
  double getTargetFps() const;
  std::string getDebugHostname() const;
  uint32_t getDebugPort() const;
};

#endif // GLOBAL_CONFIGS_H
