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

public:
  GraphicEngine();
  void preloadTextures();
  SDL2pp::Renderer &getSdlRendererReference();

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

#endif // GRAPHIC_ENGINE_H