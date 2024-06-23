#include "./global_configs.h"
#include "jjr2_error.h"
#include <cstdint>
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

  this->backgroundMusicVolumeLobby =
      gameConfigs["background_music_volume_lobby"].as<uint32_t>();
  this->backgroundMusicVolumeGame =
      gameConfigs["background_music_volume_game"].as<uint32_t>();
  this->shouldPlayBackgroundMusic =
      gameConfigs["play_background_music"].as<bool>();

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
  this->bullet1Cooldown = gameConfigs["bullet_1_cooldown"].as<double>();

  this->bullet2MaxAmmo = gameConfigs["bullet_2_max_ammo"].as<uint16_t>();
  this->bullet2Speed = gameConfigs["bullet_2_speed"].as<uint8_t>();
  this->bullet2Damage = gameConfigs["bullet_2_damage"].as<uint8_t>();
  this->bullet2Cooldown = gameConfigs["bullet_2_cooldown"].as<double>();

  this->respawnTime = gameConfigs["respawn_time"].as<double>();

  this->carrotHeal = gameConfigs["carrot_heal"].as<uint16_t>();
  this->intoxicatedTime = gameConfigs["intoxicated_time"].as<double>();
  this->pointsPerCoin = gameConfigs["points_per_coin"].as<uint32_t>();
  this->pointsPerGem = gameConfigs["points_per_gem"].as<uint32_t>();

  this->bubbaMaxLife = gameConfigs["bubba_max_life"].as<uint8_t>();
  this->bubbaDamage = gameConfigs["bubba_damage"].as<uint8_t>();
  this->bubbaPoints = gameConfigs["bubba_points"].as<uint32_t>();
  this->bubbaRespawnTime = gameConfigs["bubba_respawn_time"].as<double>();
  this->bubbaAmmoDropChance = gameConfigs["bubba_ammo_drop_chance"].as<float>();
  this->bubbaHealthDropChance =
      gameConfigs["bubba_health_drop_chance"].as<float>();

  this->turtleMaxLife = gameConfigs["turtle_max_life"].as<uint8_t>();
  this->turtleDamage = gameConfigs["turtle_damage"].as<uint8_t>();
  this->turtlePoints = gameConfigs["turtle_points"].as<uint32_t>();
  this->turtleRespawnTime = gameConfigs["turtle_respawn_time"].as<double>();
  this->turtleAmmoDropChance =
      gameConfigs["turtle_ammo_drop_chance"].as<float>();
  this->turtleHealthDropChance =
      gameConfigs["turtle_health_drop_chance"].as<float>();

  this->schwarzenguardMaxLife =
      gameConfigs["schwarzenguard_max_life"].as<uint8_t>();
  this->schwarzenguardDamage =
      gameConfigs["schwarzenguard_damage"].as<uint8_t>();
  this->schwarzenguardPoints =
      gameConfigs["schwarzenguard_points"].as<uint32_t>();
  this->schwarzenguardRespawnTime =
      gameConfigs["schwarzenguard_respawn_time"].as<double>();
  this->schwarzenguardAmmoDropChance =
      gameConfigs["schwarzenguard_ammo_drop_chance"].as<float>();
  this->schwarzenguardHealthDropChance =
      gameConfigs["schwarzenguard_health_drop_chance"].as<float>();
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

uint32_t GlobalConfigs::getBackgroundMusicVolumeLobby() const {
  return this->backgroundMusicVolumeLobby;
}

uint32_t GlobalConfigs::getBackgroundMusicVolumeGame() const {
  return this->backgroundMusicVolumeGame;
}

bool GlobalConfigs::getShouldPlayBackgroundMusic() const {
  return this->shouldPlayBackgroundMusic;
}

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

double GlobalConfigs::getBullet1Cooldown() const {
  return this->bullet1Cooldown;
}

uint16_t GlobalConfigs::getBullet2MaxAmmo() const {
  return this->bullet2MaxAmmo;
}

uint8_t GlobalConfigs::getBullet2Speed() const { return this->bullet2Speed; }

uint8_t GlobalConfigs::getBullet2Damage() const { return this->bullet2Damage; }

double GlobalConfigs::getBullet2Cooldown() const {
  return this->bullet2Cooldown;
}

double GlobalConfigs::getRespawnTime() const { return this->respawnTime; }

uint16_t GlobalConfigs::getCarrotHeal() const { return this->carrotHeal; }

double GlobalConfigs::getIntoxicatedTime() const {
  return this->intoxicatedTime;
}

uint32_t GlobalConfigs::getPointsPerCoin() const { return this->pointsPerCoin; }

uint32_t GlobalConfigs::getPointsPerGem() const { return this->pointsPerGem; }

uint8_t GlobalConfigs::getBubbaMaxLife() const { return this->bubbaMaxLife; }

uint8_t GlobalConfigs::getBubbaDamage() const { return this->bubbaDamage; }

uint32_t GlobalConfigs::getBubbaPoints() const { return this->bubbaPoints; }

double GlobalConfigs::getBubbaRespawnTime() const {
  return this->bubbaRespawnTime;
}

float GlobalConfigs::getBubbaAmmoDropChance() const {
  return this->bubbaAmmoDropChance;
}

float GlobalConfigs::getBubbaHealthDropChance() const {
  return this->bubbaHealthDropChance;
}

uint8_t GlobalConfigs::getTurtleMaxLife() const { return this->turtleMaxLife; }

uint8_t GlobalConfigs::getTurtleDamage() const { return this->turtleDamage; }

uint32_t GlobalConfigs::getTurtlePoints() const { return this->turtlePoints; }

double GlobalConfigs::getTurtleRespawnTime() const {
  return this->turtleRespawnTime;
}

float GlobalConfigs::getTurtleAmmoDropChance() const {
  return this->turtleAmmoDropChance;
}

float GlobalConfigs::getTurtleHealthDropChance() const {
  return this->turtleHealthDropChance;
}

uint8_t GlobalConfigs::getSchwarzenguardMaxLife() const {
  return this->schwarzenguardMaxLife;
}

uint8_t GlobalConfigs::getSchwarzenguardDamage() const {
  return this->schwarzenguardDamage;
}

uint32_t GlobalConfigs::getSchwarzenguardPoints() const {
  return this->schwarzenguardPoints;
}

double GlobalConfigs::getSchwarzenguardRespawnTime() const {
  return this->schwarzenguardRespawnTime;
}

float GlobalConfigs::getSchwarzenguardAmmoDropChance() const {
  return this->schwarzenguardAmmoDropChance;
}

float GlobalConfigs::getSchwarzenguardHealthDropChance() const {
  return this->schwarzenguardHealthDropChance;
}
