#include "./jazz.h"
#include <unordered_map>

static const std::string INITIAL_STATE = "idle1";

static const std::unordered_map<std::string, int> MOVING_DIRECTIONS = {
    {"left", 0}, {"right", 1}, {"up", 2}, {"down", 3}};

Jazz::Jazz(GraphicEngine &graphicEngine, Coordinates &currentCoords)
    : graphicEngine(graphicEngine),
      currentState(&this->graphicEngine.getJazzGenericSprite(INITIAL_STATE)),
      currentFrame(0), currentCoords(currentCoords), isWalkingLeft(false),
      isWalkingRight(false), isWalkingUp(false), isWalkingDown(false),
      isRunning(false) {}

void Jazz::debugUpdateLocation(int iterationNumber) {
  int speed = 0;
  bool isWalking = this->isWalkingLeft || this->isWalkingRight ||
                   this->isWalkingUp || this->isWalkingDown;

  if (isWalking) {
    speed = 5;
  } else if (this->isRunning) {
    speed = 10;
  }

  if (this->isWalkingLeft)
    this->currentCoords.setX(this->currentCoords.getX() - speed);
  if (this->isWalkingRight)
    this->currentCoords.setX(this->currentCoords.getX() + speed);
  if (this->isWalkingUp)
    this->currentCoords.setY(this->currentCoords.getY() - speed);
  if (this->isWalkingDown)
    this->currentCoords.setY(this->currentCoords.getY() + speed);
}

void Jazz::render(int iterationNumber) {
  this->currentFrame = iterationNumber % this->currentState->maxAnimationFrames;
  this->debugUpdateLocation(iterationNumber);

  // Pick sprite from running animantion sequence
  int spriteX = this->currentState->spriteCoords[this->currentFrame].getX();
  int spriteY = this->currentState->spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->currentState->width[this->currentFrame];
  int spriteHeight = this->currentState->height[this->currentFrame];

  int positionX = this->currentCoords.getX();
  int positionY = this->currentCoords.getY();

  // Draw player sprite
  this->currentState->sdlRenderer.Copy(
      this->currentState->texture,
      SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY - spriteHeight, spriteWidth,
                   spriteHeight));
}

void Jazz::render(int iterationNumber, Coordinates &coords) {
  this->currentFrame = iterationNumber % this->currentState->maxAnimationFrames;
  this->debugUpdateLocation(iterationNumber);

  // Pick sprite from running animantion sequence
  int spriteX = this->currentState->spriteCoords[this->currentFrame].getX();
  int spriteY = this->currentState->spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->currentState->width[this->currentFrame];
  int spriteHeight = this->currentState->height[this->currentFrame];

  int positionX = coords.getX();
  int positionY = coords.getY();

  // Draw player sprite
  this->currentState->sdlRenderer.Copy(
      this->currentState->texture,
      SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY - spriteHeight, spriteWidth,
                   spriteHeight));
}

void Jazz::update(bool isWalking, bool isRunning, std::string movingDirection) {

  bool wasWalking = this->isWalkingLeft || this->isWalkingRight ||
                    this->isWalkingUp || this->isWalkingDown;

  this->isRunning = isRunning;
  this->movingDirection = movingDirection;

  if (movingDirection == "left") {
    this->isWalkingLeft = isWalking;
  } else if (movingDirection == "right") {
    this->isWalkingRight = isWalking;

  } else if (movingDirection == "up") {
    this->isWalkingUp = isWalking;

  } else if (movingDirection == "down") {
    this->isWalkingDown = isWalking;
  }

  bool isNowWalking = this->isWalkingLeft || this->isWalkingRight ||
                      this->isWalkingUp || this->isWalkingDown;

  if (wasWalking && !isNowWalking) {
    this->currentState = &this->graphicEngine.getJazzGenericSprite("idle1");
  } else if (!wasWalking && isNowWalking) {
    this->currentState = &this->graphicEngine.getJazzGenericSprite("walking");
  }
}

void Jazz::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Jazz::renderFromLeftCorner(int iterationNumber,
                                const Coordinates &leftCorner) {

  this->currentFrame = iterationNumber % this->currentState->maxAnimationFrames;

  // Pick sprite from running animantion sequence
  int spriteX = this->currentState->spriteCoords[this->currentFrame].getX();
  int spriteY = this->currentState->spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->currentState->width[this->currentFrame];
  int spriteHeight = this->currentState->height[this->currentFrame];

  int positionX = this->currentCoords.getX() - leftCorner.getX();
  int positionY = this->currentCoords.getY() - leftCorner.getY();

  // Draw player sprite
  this->currentState->sdlRenderer.Copy(
      this->currentState->texture,
      SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY - spriteHeight, spriteWidth,
                   spriteHeight));
}

Jazz::~Jazz() {}
