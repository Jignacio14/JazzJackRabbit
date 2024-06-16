#include "./hud.h"

#include "../../../common/global_configs.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

static const int HUD_HORIZONTAL_SIZE = 150; // In px
static const int WHITE_RGBA[4] = {255, 255, 255, 255};
static const int BLACK_RGBA[4] = {0, 0, 0, 255};

const static char EMPTY_POINTS_TEXT[] = "POINTS: 0";
const static int FONT_SIZE = 12;
const static SDL2pp::Color TEXT_COLOR = SDL2pp::Color(255, 255, 255, 255);

Hud::Hud(GraphicEngine &graphicEngine, Player &player)
    : graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      player(player), hudLeftCorner(SCREEN_SIZE_X - HUD_HORIZONTAL_SIZE, 0),
      hudWidth(HUD_HORIZONTAL_SIZE), hudHeight(SCREEN_SIZE_Y),
      frameSprite(this->graphicEngine.getHudSprite(HudSpriteCodes::Frame)),
      jazzHudIcon(this->graphicEngine.getJazzHudIcon()),
      spazHudIcon(this->graphicEngine.getSpazHudIcon()),
      loriHudIcon(this->graphicEngine.getLoriHudIcon()),
      pointsText(this->sdlRenderer, EMPTY_POINTS_TEXT, TEXT_COLOR, FONT_SIZE,
                 TextFontsCodes::Joystix) {}

void Hud::renderBackgroundFrame() {
  int spriteWidth = this->frameSprite.width[0];
  int spriteHeight = this->frameSprite.height[0];

  this->sdlRenderer.Copy(
      this->frameSprite.texture, SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
      SDL2pp::Rect(this->hudLeftCorner.getX(), this->hudLeftCorner.getY(),
                   spriteWidth, spriteHeight));
}

Sprite &Hud::getHudIcon(const PlayerDto &playerinfo) {
  if (playerinfo.type == PlayableCharactersIds::Jazz) {
    return this->jazzHudIcon;
  } else if (playerinfo.type == PlayableCharactersIds::Spaz) {
    return this->spazHudIcon;
  } else /* if (playerinfo.type == PlayableCharactersIds::Lori) */ {
    return this->loriHudIcon;
  }
}

void Hud::renderHudIcon(const PlayerDto &playerinfo) {
  Sprite &hudIconSprite = this->getHudIcon(playerinfo);

  int spriteWidth = hudIconSprite.width[0];
  int spriteHeight = hudIconSprite.height[0];

  int positionX = this->hudLeftCorner.getX() + 20;
  int positionY = this->hudLeftCorner.getY() + 15;

  this->sdlRenderer.Copy(
      hudIconSprite.texture, SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));
}

void Hud::renderPoints(const PlayerDto &playerinfo) {
  std::string text = "POINTS:\n" + std::to_string(100);
  this->pointsText.updateInnerText(text);

  int positionX = this->hudLeftCorner.getX() + 62;
  int positionY = this->hudLeftCorner.getY() + 18;
  Coordinates coords(positionX, positionY);
  this->pointsText.render(coords);
}

void Hud::render(int iterationNumber) {
  const PlayerDto &playerinfo = this->player.getPlayerDtoReference();

  this->renderBackgroundFrame();
  this->renderHudIcon(playerinfo);
  this->renderPoints(playerinfo);
}

void Hud::render(int iterationNumber, Coordinates &coords) {}

void Hud::renderFromLeftCorner(int iterationNumber,
                               const Coordinates &leftCorner) {}

int Hud::getHorizontalSize() { return HUD_HORIZONTAL_SIZE; }

uint8_t Hud::getId() const { return 255; }

Hud::~Hud() {}
