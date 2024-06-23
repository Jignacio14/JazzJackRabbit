#ifndef JAZZJACKRABBIT_CONVENTION_H
#define JAZZJACKRABBIT_CONVENTION_H

#include <cstdint>

struct PlayerCommands {
  // cppcheck-suppress unusedStructMember
  static const uint8_t MOVE_LEFT = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t MOVE_RIGHT = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t JUMP = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t STOP_MOVING = 3;
  // cppcheck-suppress unusedStructMember
  static const uint8_t SHOOT = 4;
  // cppcheck-suppress unusedStructMember
  static const uint8_t STOP_SHOOTING = 5;
  // cppcheck-suppress unusedStructMember
  static const uint8_t CHANGE_WEAPON = 6;
  // cppcheck-suppress unusedStructMember
  static const uint8_t SPECIAL_ATTACK = 7;
  // cppcheck-suppress unusedStructMember
  static const uint8_t RUN = 8;
  // cppcheck-suppress unusedStructMember
  static const uint8_t STOP_RUNNING = 9;
};

struct PlayableCharactersIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Jazz = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Spaz = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Lori = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t NoneSelected = 9;
};

struct GunsIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Gun1 = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Gun2 = 2;
};

struct NumericBool {
  // cppcheck-suppress unusedStructMember
  static const uint8_t True = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t False = 1;
};

struct FacingDirectionsIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Left = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Right = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Up = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Down = 3;
};

struct CollectableIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Coin = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Diamond = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Carrot = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t AmmoGun1 = 3;
  // cppcheck-suppress unusedStructMember
  static const uint8_t AmmoGun2 = 4;
};

struct EnemiesIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Bubba = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t TurtleGoon = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Schwarzenguard = 2;
};

struct GeneralType {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Player = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Enemy = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Collectable = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Bullet = 3;
};

struct ScenariosIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Carrotus = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t BeachWorld = 1;
};

struct HitboxSizes {
  // cppcheck-suppress unusedStructMember
  static const uint8_t PlayerWidth = 40;
  // cppcheck-suppress unusedStructMember
  static const uint8_t PlayerHeight = 50;
  // cppcheck-suppress unusedStructMember
  static const uint8_t EnemyWidth = 50;
  // cppcheck-suppress unusedStructMember
  static const uint8_t EnemyHeight = 50;
  // cppcheck-suppress unusedStructMember
  static const uint8_t CollectableWidth = 25;
  // cppcheck-suppress unusedStructMember
  static const uint8_t CollectableHeight = 25;
  // cppcheck-suppress unusedStructMember
  static const uint8_t BulletWidth = 10;
  // cppcheck-suppress unusedStructMember
  static const uint8_t BulletHeight = 10;
};

struct EnemyDrop {
  // cppcheck-suppress unusedStructMember
  static const uint8_t NoDrop = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Ammo = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Carrot = 2;
};

#endif // JAZZJACKRABBIT_CONVENTION_H
