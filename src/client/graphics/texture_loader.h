#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "./sprite.h"
#include <SDL2pp/SDL2pp.hh>
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

public:
  explicit TextureLoader(SDL2pp::Renderer &sdlRenderer);
  void preloadTextures();
};

#endif // TEXTURE_LOADER_H