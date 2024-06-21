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
};

#endif // GLOBAL_CONFIGS_H
