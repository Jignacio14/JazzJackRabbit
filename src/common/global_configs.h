#ifndef GLOBAL_CONFIGS_H
#define GLOBAL_CONFIGS_H

#include <cstdint>
#include <string>

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
  uint32_t backgroundMusicVolumeLobby;
  // cppcheck-suppress unusedStructMember
  uint32_t backgroundMusicVolumeGame;
  // cppcheck-suppress unusedStructMember
  bool shouldPlayBackgroundMusic;
  // cppcheck-suppress unusedStructMember
  int screenSizeX;
  // cppcheck-suppress unusedStructMember
  int screenSizeY;
  // cppcheck-suppress unusedStructMember
  std::string windowName;
  // cppcheck-suppress unusedStructMember
  double targetFps;
  // cppcheck-suppress unusedStructMember
  uint32_t playerStartingPoints;
  // cppcheck-suppress unusedStructMember
  uint32_t playerMaxLife;
  // cppcheck-suppress unusedStructMember
  uint32_t playerStartingAmmoGun1;
  // cppcheck-suppress unusedStructMember
  uint32_t playerStartingAmmoGun2;
  // cppcheck-suppress unusedStructMember
  uint32_t ticksPerSecondOfServer;
  // cppcheck-suppress unusedStructMember
  uint32_t maxInstructionsPerTickOfServer;
  // cppcheck-suppress unusedStructMember
  uint32_t maxPlayersInHudLeaderboard;

  // cppcheck-suppress unusedStructMember
  uint16_t bullet1MaxAmmo;
  // cppcheck-suppress unusedStructMember
  uint8_t bullet1Speed;
  // cppcheck-suppress unusedStructMember
  uint8_t bullet1Damage;
  // cppcheck-suppress unusedStructMember
  double bullet1Cooldown;

  // cppcheck-suppress unusedStructMember
  uint16_t bullet2MaxAmmo;
  // cppcheck-suppress unusedStructMember
  uint8_t bullet2Speed;
  // cppcheck-suppress unusedStructMember
  uint8_t bullet2Damage;
  // cppcheck-suppress unusedStructMember
  double bullet2Cooldown;
  // cppcheck-suppress unusedStructMember
  double respawnTime;

  // cppcheck-suppress unusedStructMember
  uint16_t carrotHeal;
  // cppcheck-suppress unusedStructMember
  uint16_t carrotPoisonedChance;
  // cppcheck-suppress unusedStructMember
  double intoxicatedTime;
  // cppcheck-suppress unusedStructMember
  uint32_t pointsPerCoin;
  // cppcheck-suppress unusedStructMember
  uint32_t pointsPerGem;

  // cppcheck-suppress unusedStructMember
  uint8_t bubbaMaxLife;
  // cppcheck-suppress unusedStructMember
  uint8_t bubbaDamage;
  // cppcheck-suppress unusedStructMember
  uint32_t bubbaPoints;
  // cppcheck-suppress unusedStructMember
  double bubbaRespawnTime;
  // cppcheck-suppress unusedStructMember
  float bubbaAmmoDropChance;
  // cppcheck-suppress unusedStructMember
  float bubbaHealthDropChance;

  // cppcheck-suppress unusedStructMember
  uint8_t turtleMaxLife;
  // cppcheck-suppress unusedStructMember
  uint8_t turtleDamage;
  // cppcheck-suppress unusedStructMember
  uint32_t turtlePoints;
  // cppcheck-suppress unusedStructMember
  double turtleRespawnTime;
  // cppcheck-suppress unusedStructMember
  float turtleAmmoDropChance;
  // cppcheck-suppress unusedStructMember
  float turtleHealthDropChance;

  // cppcheck-suppress unusedStructMember
  uint8_t schwarzenguardMaxLife;
  // cppcheck-suppress unusedStructMember
  uint8_t schwarzenguardDamage;
  // cppcheck-suppress unusedStructMember
  uint32_t schwarzenguardPoints;
  // cppcheck-suppress unusedStructMember
  double schwarzenguardRespawnTime;
  // cppcheck-suppress unusedStructMember
  float schwarzenguardAmmoDropChance;
  // cppcheck-suppress unusedStructMember
  float schwarzenguardHealthDropChance;

  // cppcheck-suppress unusedStructMember
  uint8_t specialAttackDamage;

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

  uint16_t getMaxPlayersPerGame() const;
  uint32_t getMaxGameDuration() const;
  uint32_t getMaxUsernameLength() const;
  uint32_t getMinNumberOfPlayers() const;
  uint32_t getMaxPortNumber() const;
  uint32_t getBackgroundMusicVolumeLobby() const;
  uint32_t getBackgroundMusicVolumeGame() const;
  bool getShouldPlayBackgroundMusic() const;
  int getScreenSizeX() const;
  int getScreenSizeY() const;
  std::string getWindowName() const;
  double getTargetFps() const;
  uint32_t getPlayerStartingPoints() const;
  uint32_t getPlayerMaxLife() const;
  uint32_t getPlayerStartingAmmoGun1() const;
  uint32_t getPlayerStartingAmmoGun2() const;
  uint32_t getTargetTicksPerSecondOfServer() const;
  uint32_t getMaxInstructionsPerTickOfServer() const;
  uint32_t getMaxPlayersInHudLeaderboard() const;
  uint16_t getBullet1MaxAmmo() const;
  uint8_t getBullet1Speed() const;
  uint8_t getBullet1Damage() const;
  double getBullet1Cooldown() const;
  uint16_t getBullet2MaxAmmo() const;
  uint8_t getBullet2Speed() const;
  uint8_t getBullet2Damage() const;
  double getBullet2Cooldown() const;
  double getRespawnTime() const;
  uint16_t getCarrotHeal() const;
  uint16_t getCarrotPoisonedChance() const;
  double getIntoxicatedTime() const;
  uint32_t getPointsPerCoin() const;
  uint32_t getPointsPerGem() const;

  uint8_t getBubbaMaxLife() const;
  uint8_t getBubbaDamage() const;
  uint32_t getBubbaPoints() const;
  double getBubbaRespawnTime() const;
  float getBubbaAmmoDropChance() const;
  float getBubbaHealthDropChance() const;

  uint8_t getTurtleMaxLife() const;
  uint8_t getTurtleDamage() const;
  uint32_t getTurtlePoints() const;
  double getTurtleRespawnTime() const;
  float getTurtleAmmoDropChance() const;
  float getTurtleHealthDropChance() const;

  uint8_t getSchwarzenguardMaxLife() const;
  uint8_t getSchwarzenguardDamage() const;
  uint32_t getSchwarzenguardPoints() const;
  double getSchwarzenguardRespawnTime() const;
  float getSchwarzenguardAmmoDropChance() const;
  float getSchwarzenguardHealthDropChance() const;

  uint8_t getSpecialAttackDamage() const;
};

#endif // GLOBAL_CONFIGS_H
