#ifndef GLOBAL_CONFIGS_H
#define GLOBAL_CONFIGS_H

#include <cstdint>

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

  uint16_t getMaxPlayersPerGame();
  uint32_t getMaxGameDuration();
  uint32_t getMaxUsernameLength();
  uint32_t getMinNumberOfPlayers();
  uint32_t getMaxPortNumber();
  int getScreenSizeX();
  int getScreenSizeY();
};

#endif // GLOBAL_CONFIGS_H
