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

struct SpriteNamesMap {
  // cppcheck-suppress unusedStructMember
  const std::map<uint8_t, std::string> map;
  SpriteNamesMap();
};

/*const std::map<const uint8_t, std::string> SpriteNamesMap{
    {GenericSpriteCodes::Death, "death"},
    {GenericSpriteCodes::HudIcon, "hud_icon"},
    {GenericSpriteCodes::Hurt, "hurt"},
    {GenericSpriteCodes::Idle, "idle"},
    {GenericSpriteCodes::IntoxicatedIdle, "intoxicated_idle"},
    {GenericSpriteCodes::IntoxicatedWalking, "intoxicated_walking"},
    {GenericSpriteCodes::Jumping, "jumping"},
    {GenericSpriteCodes::Landing, "landing"},
    {GenericSpriteCodes::Falling, "falling"},
    {GenericSpriteCodes::Running, "running"},
    {GenericSpriteCodes::Shooting, "shooting"},
    {GenericSpriteCodes::Walking, "walking"},
    {JazzSpecialsCodes::Uppercut, "uppercut"},
    {SpazSpecialsCodes::SideKick, "side_kick"},
    {LoriSpecialsCodes::ShortKick, "short_kick"},
    {ScenarioSpriteCodes::Background, "background"},
    {ScenarioSpriteCodes::Decoration, "decoration"},
    {ScenarioSpriteCodes::TopGrass, "top_grass"},
    {ScenarioSpriteCodes::FullDirt, "full_dirt"},
};*/

#endif // SPRITE_PROPS_H