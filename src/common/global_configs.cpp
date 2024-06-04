#include "./global_configs.h"
#include "jjr2_error.h"
#include <yaml-cpp/yaml.h>

const static char GAME_CONFIGURATION_FILE_PATH[] = "games_config.yaml";

GlobalConfigs &GlobalConfigs::getInstance() {
  static GlobalConfigs globalConfigs;
  return globalConfigs;
}

GlobalConfigs::GlobalConfigs() {
  YAML::Node gameConfigs = YAML::LoadFile(GAME_CONFIGURATION_FILE_PATH);

  this->maxPlayersPerGame = gameConfigs["max_players_per_game"].as<uint16_t>();
  this->maxGameDuration = gameConfigs["max_game_duration"].as<uint32_t>();
}

uint16_t GlobalConfigs::getMaxPlayersPerGame() {
  return this->maxPlayersPerGame;
}
uint32_t GlobalConfigs::getMaxGameDuration() { return this->maxGameDuration; }
