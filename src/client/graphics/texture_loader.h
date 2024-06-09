#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "./sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <memory>
#include <string>
#include <cstdint>
#include <unordered_map>

class TextureLoader {
private:
  SDL2pp::Renderer &sdlRenderer;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, Sprite> jazzGenericSprites;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, Sprite> jazzSpecial;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> jazzHudIcon;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, Sprite> spazGenericSprites;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, Sprite> spazSpecial;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> spazHudIcon;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, Sprite> loriGenericSprites;
  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, Sprite> loriSpecial;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> loriHudIcon;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<uint8_t, Sprite> carrotusScenarioSprites;

public:
  explicit TextureLoader(SDL2pp::Renderer &sdlRenderer);
  void preloadTextures();

  Sprite &getJazzGenericSprite(const std::string &spriteName);
  Sprite &getJazzSpecialSprite(const std::string &spriteName);
  Sprite &getJazzHudIcon();

  Sprite &getSpazGenericSprite(const std::string &spriteName);
  Sprite &getSpazSpecialSprite(const std::string &spriteName);
  Sprite &getSpazHudIcon();

  Sprite &getLoriGenericSprite(const std::string &spriteName);
  Sprite &getLoriSpecialSprite(const std::string &spriteName);
  Sprite &getLoriHudIcon();

  Sprite &getCarrotusScenarioSprite(const std::string &spriteName);
};

#endif // TEXTURE_LOADER_H