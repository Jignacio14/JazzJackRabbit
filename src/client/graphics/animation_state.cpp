#include "./animation_state.h"
#include <string>

#include "../../common/global_configs.h"
#include "../../data/hitbox_sizes.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();
const static double TARGET_FPS = globalConfigs.getTargetFps();
const static double RATE = ((double)1) / TARGET_FPS;

AnimationState::AnimationState(GraphicEngine &graphicEngine,
                               const uint8_t &spriteCode, Sprite *sprite,
                               const bool &shouldCycle,
                               const double &slowdownCoefficient,
                               const bool &shouldFlip)
    : shouldCycle(shouldCycle), shouldFlip(shouldFlip),
      slowdownCoefficient(slowdownCoefficient * RATE),
      graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      currentFrame(0), hasFinished(false), totalRenders(0),
      spriteCode(spriteCode), sprite(sprite) {}

bool AnimationState::shouldRenderLastFrame() const {
  if (!this->shouldCycle &&
      this->totalRenders >= this->sprite->maxAnimationFrames) {
    return true;
  }
  return false;
}

void AnimationState::renderFrame(int positionX, int positionY) {
  // Pick sprite from running animantion sequence
  int spriteX = this->sprite->spriteCoords[this->currentFrame].getX();
  int spriteY = this->sprite->spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->sprite->width[this->currentFrame];
  int spriteHeight = this->sprite->height[this->currentFrame];

  int deltaY = HitboxSizes::PlayerHeight - spriteHeight;

  if (!this->shouldFlip) {
    this->sdlRenderer.Copy(
        this->sprite->texture,
        SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
        SDL2pp::Rect(positionX, positionY + deltaY, spriteWidth, spriteHeight));
  } else {
    double rotationDegrees = 0.0;
    auto &rotationCenter = SDL2pp::NullOpt;
    this->sdlRenderer.Copy(
        this->sprite->texture,
        SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
        SDL2pp::Rect(positionX, positionY + deltaY, spriteWidth, spriteHeight),
        rotationDegrees, rotationCenter, SDL_FLIP_HORIZONTAL);
  }
}

void AnimationState::renderLastFrameFromLeftCorner(
    const int &iterationNumber, const Coordinates &leftCorner,
    const Coordinates &currentCoords) {
  int positionX = currentCoords.getX() - leftCorner.getX();
  int positionY = currentCoords.getY() - leftCorner.getY();

  this->currentFrame = this->sprite->maxAnimationFrames - 1;

  this->renderFrame(positionX, positionY);
}

void AnimationState::renderLastFrame(const int &iterationNumber,
                                     const Coordinates &coords) {
  int positionX = coords.getX();
  int positionY = coords.getY();

  this->currentFrame = this->sprite->maxAnimationFrames - 1;

  this->renderFrame(positionX, positionY);
}

void AnimationState::render(int iterationNumber, const Coordinates &coords) {
  if (this->shouldRenderLastFrame()) {
    this->renderLastFrame(iterationNumber, coords);
  }

  int newIterationNumber = this->slowdownCoefficient * iterationNumber;
  this->currentFrame = newIterationNumber % this->sprite->maxAnimationFrames;

  int positionX = coords.getX();
  int positionY = coords.getY();

  this->renderFrame(positionX, positionY);
  this->totalRenders++;
}

void AnimationState::renderFromLeftCorner(int iterationNumber,
                                          const Coordinates &leftCorner,
                                          const Coordinates &currentCoords) {
  if (this->shouldRenderLastFrame()) {
    this->renderLastFrameFromLeftCorner(iterationNumber, leftCorner,
                                        currentCoords);
  }

  int newIterationNumber = this->slowdownCoefficient * iterationNumber;
  this->currentFrame = newIterationNumber % this->sprite->maxAnimationFrames;

  int positionX = currentCoords.getX() - leftCorner.getX();
  int positionY = currentCoords.getY() - leftCorner.getY();

  this->renderFrame(positionX, positionY);
  this->totalRenders++;
}

bool AnimationState::canBreakAnimation() const {
  if (this->shouldCycle || this->shouldRenderLastFrame()) {
    return true;
  }
  return false;
}
