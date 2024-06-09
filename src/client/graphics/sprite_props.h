#ifndef SPRITE_PROPS_H
#define SPRITE_PROPS_H

#include <cstdint>

struct GenericSpriteNames {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Death = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t HudIcon = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Hurt = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Idle = 3;
  // cppcheck-suppress unusedStructMember
  static const uint8_t IntoxicatedIdle = 4;
  // cppcheck-suppress unusedStructMember
  static const uint8_t IntoxicatedWalking = 5;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Jumping = 6;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Landing = 7;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Falling = 8;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Running = 9;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Shooting = 10;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Walking = 11;
};

struct JazzSpecials {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Uppercut = 30;
};

struct SpazSpecials {
  // cppcheck-suppress unusedStructMember
  static const uint8_t SideKick = 40;
};

struct LoriSpecials {
  // cppcheck-suppress unusedStructMember
  static const uint8_t ShortKick = 50;
};

struct ScenarioSpriteNames {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Background = 60;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Decoration = 61;
  // cppcheck-suppress unusedStructMember
  static const uint8_t TopGrass = 62;
  // cppcheck-suppress unusedStructMember
  static const uint8_t FullDirt = 63;
};

#endif // SPRITE_PROPS_H