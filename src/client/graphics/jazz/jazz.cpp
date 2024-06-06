#include "./jazz.h"

static const std::string INITIAL_STATE = "idle1";

Jazz::Jazz(GraphicEngine &graphicEngine)
    : graphicEngine(graphicEngine),
      currentState(this->graphicEngine.getJazzGenericSprite(INITIAL_STATE)),
      currentFrame(0), currentCoords(100, 100) {}

void Jazz::render(int iterationNumber) {
  this->currentFrame = iterationNumber % this->currentState.maxAnimationFrames;

  // Pick sprite from running animantion sequence
  int spriteX = this->currentState.spriteCoords[this->currentFrame].getX();
  int spriteY = this->currentState.spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->currentState.width[this->currentFrame];
  int spriteHeight = this->currentState.height[this->currentFrame];

  int positionX = this->currentCoords.getX();
  positionX += 5;

  if (positionX > this->currentState.sdlRenderer.GetOutputWidth())
    positionX = -50;

  this->currentCoords.setX(positionX);

  int positionY = this->currentState.sdlRenderer.GetOutputHeight() /
                  2; // this->currentCoords.getY();

  // Draw player sprite
  this->currentState.sdlRenderer.Copy(
      this->currentState.texture,
      SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY - spriteHeight, spriteWidth,
                   spriteHeight));
}

Jazz::~Jazz() {}
