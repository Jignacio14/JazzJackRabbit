#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

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
};

#endif // GRAPHIC_ENGINE_H