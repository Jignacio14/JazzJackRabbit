#ifndef GAME_CONFIGS_H
#define GAME_CONFIGS_H

#include <cstdint>
#include <string>

class GameConfigs {
private:
  // cppcheck-suppress unusedStructMember
  std::string ownerName;
  // cppcheck-suppress unusedStructMember
  uint32_t maxNumberOfPlayers;
  // cppcheck-suppress unusedStructMember
  uint32_t currentNumberOfPlayers;
  // cppcheck-suppress unusedStructMember
  uint32_t gameDuration;

public:
  explicit GameConfigs();

  GameConfigs(std::string ownerName, uint32_t maxNumberOfPlayers,
              uint32_t currentNumberOfPlayers, uint32_t gameDuration);

  GameConfigs(const GameConfigs &other);
  GameConfigs &operator=(const GameConfigs &other);

  const std::string getOwnerName() const;

  const uint32_t getMaxNumberOfPlayers() const;

  const uint32_t getCurrentNumberOfPlayers() const;

  const uint32_t getGameDuration() const;
};

#endif // GAME_CONFIGS_H