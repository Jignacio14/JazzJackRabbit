#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "./sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

class TextureLoader {
private:
  SDL2pp::Renderer &sdlRenderer;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> jazzGenericSprites;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> jazzSpecial;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> jazzHudIcon;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> spazGenericSprites;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> spazSpecial;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> spazHudIcon;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> loriGenericSprites;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> loriSpecial;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> loriHudIcon;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> carrotusScenarioSprites;

public:
  explicit TextureLoader(SDL2pp::Renderer &sdlRenderer);
  void preloadTextures();

  Sprite &getJazzGenericSprite(const u_int8_t &spriteCode);
  Sprite &getJazzSpecialSprite(const u_int8_t &spriteCode);
  Sprite &getJazzHudIcon();

  Sprite &getSpazGenericSprite(const u_int8_t &spriteCode);
  Sprite &getSpazSpecialSprite(const u_int8_t &spriteCode);
  Sprite &getSpazHudIcon();

  Sprite &getLoriGenericSprite(const u_int8_t &spriteCode);
  Sprite &getLoriSpecialSprite(const u_int8_t &spriteCode);
  Sprite &getLoriHudIcon();

  Sprite &getCarrotusScenarioSprite(const u_int8_t &spriteName);
};

#endif // TEXTURE_LOADER_H