#include "./graphic_engine.h"
#include "../../common/global_configs.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

const static std::string WINDOW_NAME = globalConfigs.getWindowName();

GraphicEngine::GraphicEngine()
    : sdl(SDL_INIT_VIDEO), window(WINDOW_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE_X,
                                  SCREEN_SIZE_Y, SDL_WINDOW_SHOWN),
      sdlRenderer(window, -1, SDL_RENDERER_ACCELERATED),
      textureLoader(this->sdlRenderer) {}

void GraphicEngine::preloadTextures() { this->textureLoader.preloadTextures(); }

SDL2pp::Renderer &GraphicEngine::getSdlRendererReference() {
  return std::ref(this->sdlRenderer);
}

Sprite &GraphicEngine::getJazzGenericSprite(const std::string &spriteName) {
  return this->textureLoader.getJazzGenericSprite(spriteName);
}

Sprite &GraphicEngine::getJazzSpecialSprite(const std::string &spriteName) {
  return this->textureLoader.getJazzSpecialSprite(spriteName);
}

Sprite &GraphicEngine::getJazzHudIcon() {
  return this->textureLoader.getJazzHudIcon();
}

Sprite &GraphicEngine::getSpazGenericSprite(const std::string &spriteName) {
  return this->textureLoader.getSpazGenericSprite(spriteName);
}

Sprite &GraphicEngine::getSpazSpecialSprite(const std::string &spriteName) {
  return this->textureLoader.getSpazSpecialSprite(spriteName);
}

Sprite &GraphicEngine::getSpazHudIcon() {
  return this->textureLoader.getSpazHudIcon();
}

Sprite &GraphicEngine::getLoriGenericSprite(const std::string &spriteName) {
  return this->textureLoader.getLoriGenericSprite(spriteName);
}

Sprite &GraphicEngine::getLoriSpecialSprite(const std::string &spriteName) {
  return this->textureLoader.getLoriSpecialSprite(spriteName);
}

Sprite &GraphicEngine::getLoriHudIcon() {
  return this->textureLoader.getLoriHudIcon();
}

Sprite &
GraphicEngine::getCarrotusScenarioSprite(const std::string &spriteName) {
  return this->textureLoader.getCarrotusScenarioSprite(spriteName);
}
