#include "./jazz.h"
#include <unordered_map>

static const std::string INITIAL_STATE = "idle1";

static const std::unordered_map<std::string, int> MOVING_DIRECTIONS = {
    {"left", 0}, {"right", 1}, {"up", 2}, {"down", 3}};

Jazz::Jazz(GraphicEngine &graphicEngine)
    : graphicEngine(graphicEngine),
      currentState(this->graphicEngine.getJazzGenericSprite(INITIAL_STATE)),
      currentFrame(0), currentCoords(100, 100), isWalkingLeft(false),
      isWalkingRight(false), isWalkingUp(false), isWalkingDown(false),
      isRunning(false) {}

void Jazz::debugUpdateLocation() {
  int speed = 0;
  if (this->isWalkingLeft || this->isWalkingRight || this->isWalkingUp ||
      this->isWalkingDown) {
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
  this->currentFrame = iterationNumber % this->currentState.maxAnimationFrames;
  this->debugUpdateLocation();

  // Pick sprite from running animantion sequence
  int spriteX = this->currentState.spriteCoords[this->currentFrame].getX();
  int spriteY = this->currentState.spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->currentState.width[this->currentFrame];
  int spriteHeight = this->currentState.height[this->currentFrame];

  int positionX = this->currentCoords.getX();
  int positionY = this->currentCoords.getY();

  // Draw player sprite
  this->currentState.sdlRenderer.Copy(
      this->currentState.texture,
      SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY - spriteHeight, spriteWidth,
                   spriteHeight));
}

void Jazz::update(bool isWalking, bool isRunning, std::string movingDirection) {

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
}

void Jazz::updateByCoords(int x, int y) {
  this->currentCoords.setX(this->currentCoords.getX() + x);
  this->currentCoords.setY(this->currentCoords.getY() + y);
}

Jazz::~Jazz() {}
