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

Sprite &GraphicEngine::getJazzGenericSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getJazzGenericSprite(spriteCode);
}

Sprite &GraphicEngine::getJazzSpecialSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getJazzSpecialSprite(spriteCode);
}

Sprite &GraphicEngine::getJazzHudIcon() {
  return this->textureLoader.getJazzHudIcon();
}

Sprite &GraphicEngine::getSpazGenericSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getSpazGenericSprite(spriteCode);
}

Sprite &GraphicEngine::getSpazSpecialSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getSpazSpecialSprite(spriteCode);
}

Sprite &GraphicEngine::getSpazHudIcon() {
  return this->textureLoader.getSpazHudIcon();
}

Sprite &GraphicEngine::getLoriGenericSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getLoriGenericSprite(spriteCode);
}

Sprite &GraphicEngine::getLoriSpecialSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getLoriSpecialSprite(spriteCode);
}

Sprite &GraphicEngine::getLoriHudIcon() {
  return this->textureLoader.getLoriHudIcon();
}

Sprite &GraphicEngine::getCarrotusScenarioSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getCarrotusScenarioSprite(spriteCode);
}

Sprite &GraphicEngine::getGun1Sprite(const uint8_t &spriteCode) {
  return this->textureLoader.getGun1Sprite(spriteCode);
}

Sprite &GraphicEngine::getGun1HudIcon() {
  return this->textureLoader.getGun1HudIcon();
}

Sprite &GraphicEngine::getGun2Sprite(const uint8_t &spriteCode) {
  return this->textureLoader.getGun2Sprite(spriteCode);
}

Sprite &GraphicEngine::getGun2HudIcon() {
  return this->textureLoader.getGun2HudIcon();
}

Sprite &GraphicEngine::getCollectableSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getCollectableSprite(spriteCode);
}

Sprite &GraphicEngine::getBubbaSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getBubbaSprite(spriteCode);
}

Sprite &GraphicEngine::getTurtleGoonSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getTurtleGoonSprite(spriteCode);
}

Sprite &GraphicEngine::getSchwarzenguardSprite(const uint8_t &spriteCode) {
  return this->textureLoader.getSchwarzenguardSprite(spriteCode);
}
