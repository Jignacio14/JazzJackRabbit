#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "./sprite.h"
#include <SDL2/SDL_ttf.h>
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

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> gun1Sprites;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> gun1hudIcon;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> gun2Sprites;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> gun2hudIcon;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> collectablesSprites;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> bubbaSprites;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> turtleGoonSprites;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> schwarzenguardSprites;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> sfxSprites;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, Sprite> hudSprites;

  // cppcheck-suppress unusedStructMember
  std::unordered_map<std::string, SDL2pp::Font> fonts;

  // cppcheck-suppress unusedStructMember
  std::unique_ptr<Sprite> leaderboardSprite;

public:
  explicit TextureLoader(SDL2pp::Renderer &sdlRenderer);
  void preloadTextures();
  void preloadFonts();

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

  Sprite &getGun1Sprite(const u_int8_t &spriteCode);
  Sprite &getGun1HudIcon();

  Sprite &getGun2Sprite(const u_int8_t &spriteCode);
  Sprite &getGun2HudIcon();

  Sprite &getCollectableSprite(const u_int8_t &spriteCode);

  Sprite &getBubbaSprite(const u_int8_t &spriteCode);
  Sprite &getTurtleGoonSprite(const u_int8_t &spriteCode);
  Sprite &getSchwarzenguardSprite(const u_int8_t &spriteCode);

  Sprite &getSfxSprite(const u_int8_t &spriteCode);

  Sprite &getHudSprite(const u_int8_t &spriteCode);

  Sprite &getLeaderboardSprite();
};

#endif // TEXTURE_LOADER_H