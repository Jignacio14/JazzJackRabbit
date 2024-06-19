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

  this->backgroundMusicVolumeLobby =
      gameConfigs["background_music_volume_lobby"].as<uint32_t>();
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

  this->playerStartingPoints = gameConfigs["starting_points"].as<uint32_t>();
  this->playerMaxLife = gameConfigs["max_life"].as<uint32_t>();
  this->playerStartingAmmoGun1 =
      gameConfigs["starting_ammo_gun_1"].as<uint32_t>();
  this->playerStartingAmmoGun2 =
      gameConfigs["starting_ammo_gun_2"].as<uint32_t>();

  this->ticksPerSecondOfServer =
      gameConfigs["target_ticks_per_second"].as<uint32_t>();
  this->maxInstructionsPerTickOfServer =
      gameConfigs["max_instructions_per_tick"].as<uint32_t>();

  this->maxPlayersInHudLeaderboard =
      gameConfigs["max_players_in_hud_leaderboard"].as<uint32_t>();

  this->bullet1MaxAmmo = gameConfigs["bullet_1_max_ammo"].as<uint16_t>();
  this->bullet1Speed = gameConfigs["bullet_1_speed"].as<uint8_t>();
  this->bullet1Damage = gameConfigs["bullet_1_damage"].as<uint8_t>();
  this->bullet1Cooldown = gameConfigs["bullet_1_cooldown"].as<float>();

  this->bullet2MaxAmmo = gameConfigs["bullet_2_max_ammo"].as<uint16_t>();
  this->bullet2Speed = gameConfigs["bullet_2_speed"].as<uint8_t>();
  this->bullet2Damage = gameConfigs["bullet_2_damage"].as<uint8_t>();
  this->bullet2Cooldown = gameConfigs["bullet_2_cooldown"].as<float>();
}

uint32_t GlobalConfigs::getBackgroundMusicVolumeLobby() const {
  return this->backgroundMusicVolumeLobby;
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

uint32_t GlobalConfigs::getPlayerStartingPoints() const {
  return this->playerStartingPoints;
}

uint32_t GlobalConfigs::getPlayerMaxLife() const { return this->playerMaxLife; }

uint32_t GlobalConfigs::getPlayerStartingAmmoGun1() const {
  return this->playerStartingAmmoGun1;
}

uint32_t GlobalConfigs::getPlayerStartingAmmoGun2() const {
  return this->playerStartingAmmoGun2;
}

uint32_t GlobalConfigs::getTargetTicksPerSecondOfServer() const {
  return this->ticksPerSecondOfServer;
}

uint32_t GlobalConfigs::getMaxInstructionsPerTickOfServer() const {
  return this->maxInstructionsPerTickOfServer;
}

uint32_t GlobalConfigs::getMaxPlayersInHudLeaderboard() const {
  return this->maxPlayersInHudLeaderboard;
}

uint16_t GlobalConfigs::getBullet1MaxAmmo() const {
  return this->bullet1MaxAmmo;
}

uint8_t GlobalConfigs::getBullet1Speed() const { return this->bullet1Speed; }

uint8_t GlobalConfigs::getBullet1Damage() const { return this->bullet1Damage; }

float GlobalConfigs::getBullet1Cooldown() const {
  return this->bullet1Cooldown;
}

uint16_t GlobalConfigs::getBullet2MaxAmmo() const {
  return this->bullet2MaxAmmo;
}

uint8_t GlobalConfigs::getBullet2Speed() const { return this->bullet2Speed; }

uint8_t GlobalConfigs::getBullet2Damage() const { return this->bullet2Damage; }

float GlobalConfigs::getBullet2Cooldown() const {
  return this->bullet2Cooldown;
}
