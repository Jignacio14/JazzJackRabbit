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
  this->maxUsernameLength = gameConfigs["max_username_length"].as<uint32_t>();
  this->minNumberOfPlayers =
      gameConfigs["min_number_of_players"].as<uint32_t>();
  this->maxPortNumber = gameConfigs["max_port_number"].as<uint32_t>();

  this->screenSizeX = gameConfigs["screen_size_x"].as<int>();
  this->screenSizeY = gameConfigs["screen_size_y"].as<int>();
  this->windowName = gameConfigs["window_name"].as<std::string>();
  this->targetFps = gameConfigs["target_fps"].as<double>();

  this->debugHostname = gameConfigs["debug_hostname"].as<std::string>();
  this->debugPort = gameConfigs["debug_port"].as<uint32_t>();

  this->playerStartingPoints = gameConfigs["starting_points"].as<uint32_t>();
  this->playerMaxLife = gameConfigs["max_life"].as<uint32_t>();
  this->playerStartingAmmo = gameConfigs["starting_ammo"].as<uint32_t>();
}

uint16_t GlobalConfigs::getMaxPlayersPerGame() const {
  return this->maxPlayersPerGame;
}

uint32_t GlobalConfigs::getMaxGameDuration() const {
  return this->maxGameDuration;
}

uint32_t GlobalConfigs::getMaxUsernameLength() const {
  return this->maxUsernameLength;
}

uint32_t GlobalConfigs::getMinNumberOfPlayers() const {
  return this->minNumberOfPlayers;
}

uint32_t GlobalConfigs::getMaxPortNumber() const { return this->maxPortNumber; }

int GlobalConfigs::getScreenSizeX() const { return this->screenSizeX; }

int GlobalConfigs::getScreenSizeY() const { return this->screenSizeY; }

std::string GlobalConfigs::getWindowName() const { return this->windowName; }

double GlobalConfigs::getTargetFps() const { return this->targetFps; }

std::string GlobalConfigs::getDebugHostname() const {
  return this->debugHostname;
}

uint32_t GlobalConfigs::getDebugPort() const { return this->debugPort; }

uint32_t GlobalConfigs::getPlayerStartingPoints() const {
  return this->playerStartingPoints;
}

uint32_t GlobalConfigs::getPlayerMaxLife() const { return this->playerMaxLife; }

uint32_t GlobalConfigs::getPlayerStartingAmmo() const {
  return this->playerStartingAmmo;
}
