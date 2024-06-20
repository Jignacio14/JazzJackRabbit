#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "./sprite.h"
#include "./texture_loader.h"
#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <unordered_map>

class GraphicEngine {
private:
  SDL2pp::SDL sdl;
  SDL2pp::SDLTTF sdlTtf;
  SDL2pp::Window window;
  SDL2pp::Renderer sdlRenderer;
  TextureLoader textureLoader;

  Sprite &getCarrotusScenarioSprite(const u_int8_t &spriteCode);
  Sprite &getBeachWorldScenarioSprite(const u_int8_t &spriteCode);

public:
  GraphicEngine();
  void preloadTextures();
  SDL2pp::Renderer &getSdlRendererReference();

  bool isInCameraFocus(const Coordinates &leftCorner,
                       const Coordinates &coordsToCheck) const;

  Sprite &getJazzGenericSprite(const u_int8_t &spriteCode);
  Sprite &getJazzSpecialSprite(const u_int8_t &spriteCode);
  Sprite &getJazzHudIcon();

  Sprite &getSpazGenericSprite(const u_int8_t &spriteCode);
  Sprite &getSpazSpecialSprite(const u_int8_t &spriteCode);
  Sprite &getSpazHudIcon();

  Sprite &getLoriGenericSprite(const u_int8_t &spriteCode);
  Sprite &getLoriSpecialSprite(const u_int8_t &spriteCode);
  Sprite &getLoriHudIcon();

  Sprite &getScenarioSprite(const uint8_t &spriteCode,
                            const uint8_t &scenarioId);

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

  void closeWindow();
};

#endif // GRAPHIC_ENGINE_H