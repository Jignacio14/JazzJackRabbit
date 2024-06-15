#include "./hud.h"

#include "../../../common/global_configs.h"
#include "../sprite_props.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

static const int HUD_HORIZONTAL_SIZE = 150; // In px
static const int WHITE_RGBA[4] = {255, 255, 255, 255};
static const int BLACK_RGBA[4] = {0, 0, 0, 255};

Hud::Hud(GraphicEngine &graphicEngine)
    : graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      hudLeftCorner(SCREEN_SIZE_X - HUD_HORIZONTAL_SIZE, 0),
      hudWidth(HUD_HORIZONTAL_SIZE), hudHeight(SCREEN_SIZE_Y),
      frameSprite(this->graphicEngine.getHudSprite(HudSpriteCodes::Frame)),
      jazzHudIcon(this->graphicEngine.getJazzHudIcon()),
      spazHudIcon(this->graphicEngine.getSpazHudIcon()),
      loriHudIcon(this->graphicEngine.getLoriHudIcon()) {}

void Hud::renderBackgroundFrame() {
  int spriteWidth = this->frameSprite.width[0];
  int spriteHeight = this->frameSprite.height[0];

  this->sdlRenderer.Copy(
      this->frameSprite.texture, SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
      SDL2pp::Rect(this->hudLeftCorner.getX(), this->hudLeftCorner.getY(),
                   spriteWidth, spriteHeight));
}

void Hud::render(int iterationNumber) { this->renderBackgroundFrame(); }

void Hud::render(int iterationNumber, Coordinates &coords) {}

void Hud::renderFromLeftCorner(int iterationNumber,
                               const Coordinates &leftCorner) {}

int Hud::getHorizontalSize() { return HUD_HORIZONTAL_SIZE; }

uint8_t Hud::getId() const { return 255; }

Hud::~Hud() {}
