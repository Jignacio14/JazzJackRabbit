#include "game_configs.h"

GameConfigs::GameConfigs(std::string ownerName, uint32_t maxNumberOfPlayers,
                         uint32_t currentNumberOfPlayers, uint32_t gameDuration)
    : ownerName(ownerName), maxNumberOfPlayers(maxNumberOfPlayers),
      currentNumberOfPlayers(currentNumberOfPlayers),
      gameDuration(gameDuration) {}

GameConfigs::GameConfigs(const GameConfigs &other)
    : ownerName(other.ownerName), maxNumberOfPlayers(other.maxNumberOfPlayers),
      currentNumberOfPlayers(other.currentNumberOfPlayers),
      gameDuration(other.gameDuration) {}

GameConfigs &GameConfigs::operator=(const GameConfigs &other) {
  if (this == &other) {
    return *this;
  }

  this->ownerName = other.ownerName;
  this->maxNumberOfPlayers = other.maxNumberOfPlayers;
  this->currentNumberOfPlayers = other.currentNumberOfPlayers;
  this->gameDuration = other.gameDuration;

  return *this;
}

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
