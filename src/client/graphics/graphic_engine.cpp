#include "./graphic_engine.h"
#include "../../common/global_configs.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

const static char *WINDOW_NAME = globalConfigs.getWindowName().c_str();

GraphicEngine::GraphicEngine()
    : sdl(SDL_INIT_VIDEO),
      window(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
             SCREEN_SIZE_X, SCREEN_SIZE_Y, SDL_WINDOW_SHOWN),
      sdlRenderer(window, -1, SDL_RENDERER_ACCELERATED),
      textureLoader(this->sdlRenderer) {}

void GraphicEngine::preloadTextures() { this->textureLoader.preloadTextures(); }

SDL2pp::Renderer &GraphicEngine::getSdlRendererReference() {
  return std::ref(this->sdlRenderer);
}
