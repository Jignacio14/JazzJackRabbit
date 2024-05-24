#include "game_configs.h"

GameConfigs::GameConfigs(const std::string &ownerName,
                         const uint32_t &maxNumberOfPlayers,
                         const uint32_t &currentNumberOfPlayers,
                         const uint32_t &gameDuration)
    : ownerName(ownerName), maxNumberOfPlayers(maxNumberOfPlayers),
      currentNumberOfPlayers(currentNumberOfPlayers),
      gameDuration(gameDuration) {}

const std::string GameConfigs::getOwnerName() const { return this->ownerName; }

const uint32_t GameConfigs::getMaxNumberOfPlayers() const {
  return this->maxNumberOfPlayers;
}

const uint32_t GameConfigs::getCurrentNumberOfPlayers() const {
  return this->currentNumberOfPlayers;
}

const uint32_t GameConfigs::getGameDuration() const {
  return this->gameDuration;
}
