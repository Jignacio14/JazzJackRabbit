#ifndef GAME_CONFIGS_H
#define GAME_CONFIGS_H

#include <cstdint>
#include <string>

class GameConfigs {
private:
  // cppcheck-suppress unusedStructMember
  const std::string ownerName;
  // cppcheck-suppress unusedStructMember
  const uint32_t maxNumberOfPlayers;
  // cppcheck-suppress unusedStructMember
  const uint32_t currentNumberOfPlayers;
  // cppcheck-suppress unusedStructMember
  const uint32_t gameDuration;

public:
  GameConfigs(const std::string &ownerName, const uint32_t &maxNumberOfPlayers,
              const uint32_t &currentNumberOfPlayers,
              const uint32_t &gameDuration);

  const std::string getOwnerName() const;

  const uint32_t getMaxNumberOfPlayers() const;

  const uint32_t getCurrentNumberOfPlayers() const;

  const uint32_t getGameDuration() const;
};

#endif // GAME_CONFIGS_H