#ifndef GLOBAL_CONFIGS_H
#define GLOBAL_CONFIGS_H

#include <cstdint>

class GlobalConfigs {
private:
  // cppcheck-suppress unusedStructMember
  uint16_t maxPlayersPerGame;
  // cppcheck-suppress unusedStructMember
  uint32_t maxGameDuration;

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
};

#endif // GLOBAL_CONFIGS_H
