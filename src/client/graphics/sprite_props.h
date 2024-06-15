#ifndef SPRITE_PROPS_H
#define SPRITE_PROPS_H

#include <cstdint>
#include <map>
#include <string>

struct GenericSpriteCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Death = 0;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t HudIcon = 1;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Hurt = 2;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Idle = 3;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t IntoxicatedIdle = 4;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t IntoxicatedWalking = 5;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Jumping = 6;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Landing = 7;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Falling = 8;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Running = 9;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Shooting = 10;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Walking = 11;
};

struct JazzSpecialsCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Uppercut = 30;
};

struct SpazSpecialsCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t SideKick = 40;
};

struct LoriSpecialsCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t ShortKick = 50;
};

struct ScenarioSpriteCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Background = 60;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Decoration = 61;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t TopGrass = 62;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t FullDirt = 63;
};

struct GunSpriteCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t FlyingBullet = 70;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t CollectableAmmo = 71;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t HudIcon = 72;
};

struct CollectablesSpriteCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Carrot = 80;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Coin = 81;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Diamond = 82;
};

struct EnemiesGenericSpriteCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Death = 90;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Hurt = 91;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Idle = 92;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Shooting = 93;
};

struct SfxSpriteCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Impact = 100;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Shine = 101;
};

struct HudSpriteCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Frame = 110;
};

struct TextFontsCodes {
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Roboto = 120;
  // cppcheck-suppress unusedStructMember
  static constexpr uint8_t Joystix = 121;
};

struct SpriteNamesMap {
  // cppcheck-suppress unusedStructMember
  const std::map<uint8_t, std::string> map;
  SpriteNamesMap();
};

#endif // SPRITE_PROPS_H