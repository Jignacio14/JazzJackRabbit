/*#include "./jazz_idle.h"
#include <string>

static const std::string ANIMATION_KEY = "idle1";

static const double ANIMATION_SLOWDOWN_COEFFICIENT = 1.0;

JazzIdle::JazzIdle(GraphicEngine &graphicEngine)
    : graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      currentFrame(0),
      sprite(&this->graphicEngine.getJazzGenericSprite(ANIMATION_KEY)) {}

void JazzIdle::render(int iterationNumber, Coordinates &coords) {
  int newIterationNumber = ANIMATION_SLOWDOWN_COEFFICIENT * iterationNumber;
  this->currentFrame = newIterationNumber % this->sprite->maxAnimationFrames;

  // Pick sprite from running animantion sequence
  int spriteX = this->sprite->spriteCoords[this->currentFrame].getX();
  int spriteY = this->sprite->spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->sprite->width[this->currentFrame];
  int spriteHeight = this->sprite->height[this->currentFrame];

  int positionX = coords.getX();
  int positionY = coords.getY();

  this->sdlRenderer.Copy(
      this->sprite->texture,
      SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY - spriteHeight, spriteWidth,
                   spriteHeight));
}

void JazzIdle::renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner,
                                    const Coordinates &currentCoords) {
  int newIterationNumber = ANIMATION_SLOWDOWN_COEFFICIENT * iterationNumber;
  this->currentFrame = newIterationNumber % this->sprite->maxAnimationFrames;

  // Pick sprite from running animantion sequence
  int spriteX = this->sprite->spriteCoords[this->currentFrame].getX();
  int spriteY = this->sprite->spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->sprite->width[this->currentFrame];
  int spriteHeight = this->sprite->height[this->currentFrame];

  int positionX = currentCoords.getX() - leftCorner.getX();
  int positionY = currentCoords.getY() - leftCorner.getY();

  this->sdlRenderer.Copy(
      this->sprite->texture,
      SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY - spriteHeight, spriteWidth,
                   spriteHeight));
}
*/