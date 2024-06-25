#include "./disconnected_overlay.h"
#include "../../../data/convention.h"
#include "../hud/hud.h"
#include "../sprite_props.h"

const static SDL2pp::Color TEXT_COLOR = SDL2pp::Color(255, 255, 255, 255);

const static char EMPTY_TEXT[] = "-";
const static int FONT_SIZE_BIG = 35;
const static int FONT_SIZE_MEDIUM = 25;

DisconnectedOverlay::DisconnectedOverlay(SDL2pp::Renderer &sdlRenderer,
                                         AudioEngine &audioEngine,
                                         Sprite &backgroundSprite)
    : sdlRenderer(sdlRenderer), audioEngine(audioEngine),
      disconnectionSprite(backgroundSprite), didRenderOnce(false),
      gameOverText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE_BIG,
                   TextFontsCodes::Joystix),
      reasonText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE_MEDIUM,
                 TextFontsCodes::Joystix) {

  this->gameOverText.updateInnerText("GAME OVER");
  this->reasonText.updateInnerText("PLAYER DISCONNECTED");
}

void DisconnectedOverlay::renderBackground() {
  int spriteWidth = this->disconnectionSprite.width[0];
  int spriteHeight = this->disconnectionSprite.height[0];

  this->sdlRenderer.Copy(this->disconnectionSprite.texture,
                         SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
                         SDL2pp::Rect(0, 0, spriteWidth, spriteHeight));
}

void DisconnectedOverlay::renderHeader() {
  int positionX = 190;
  int positionY = 85;
  Coordinates coordsGameOver(positionX, positionY);

  this->gameOverText.render(coordsGameOver);
}

void DisconnectedOverlay::renderReason() {
  int positionX = 120;
  int positionY = 220;
  Coordinates coordsLeaderboardTitle(positionX, positionY);

  this->reasonText.render(coordsLeaderboardTitle);
}

void DisconnectedOverlay::display() {
  if (!this->didRenderOnce) {
    this->audioEngine.playDisconnectionSound();
  }

  this->didRenderOnce = true;
  this->renderBackground();
  this->renderHeader();
  this->renderReason();
}
