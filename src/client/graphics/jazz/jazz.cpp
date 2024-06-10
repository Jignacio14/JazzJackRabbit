#include "./jazz.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

/*static const std::unordered_map<std::string, int> MOVING_DIRECTIONS = {
    {"left", 0}, {"right", 1}, {"up", 2}, {"down", 3}};*/

Jazz::Jazz(GraphicEngine &graphicEngine, Coordinates &currentCoords,
           const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords),
      isWalkingLeft(false), isWalkingRight(false), isWalkingUp(false),
      isWalkingDown(false), isRunning(false), entityInfo() {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GenericSpriteCodes::Idle,
      &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Idle),
      AnimationState::Cycle, AnimationState::DefaultSlowdown,
      AnimationState::NotFlip);

  bool foundEntity = snapshot.getPlayerById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Jazz with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

/*void Jazz::debugUpdateLocation(int iterationNumber) {
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
}*/

void Jazz::render(int iterationNumber) {
  /*this->currentFrame = iterationNumber %
  this->currentState->maxAnimationFrames;
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
                   spriteHeight));*/
}

void Jazz::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Jazz::update(bool isWalking, bool isRunning, std::string movingDirection) {

  /*bool wasWalking = this->isWalkingLeft || this->isWalkingRight ||
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
  }*/
}

void Jazz::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Jazz::renderFromLeftCorner(int iterationNumber,
                                const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

Coordinates Jazz::getCoords() { return this->currentCoords; }

void Jazz::setX(int x) { this->currentCoords.setX(x); }

void Jazz::setY(int y) { this->currentCoords.setX(y); }

void Jazz::updateAnimation(const SnapshotWrapper &snapshot,
                           const PlayerDto &newEntityInfo) {

  bool shouldFlip = newEntityInfo.facing_direction == FacingDirectionsIds::Right
                        ? AnimationState::NotFlip
                        : AnimationState::Flip;

  if (newEntityInfo.is_dead == NumericBool::True) {
    if (this->entityInfo.is_dead == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Death,
          &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Death),
          AnimationState::NotCycle, AnimationState::DefaultSlowdown,
          shouldFlip);
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {
    if (this->entityInfo.was_hurt == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Hurt,
          &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Hurt),
          AnimationState::NotCycle, AnimationState::DefaultSlowdown,
          shouldFlip);
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Shooting,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Shooting),
        AnimationState::NotCycle, AnimationState::DefaultSlowdown, shouldFlip);
    return;

  } else if (newEntityInfo.shot_special == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, JazzSpecialsCodes::Uppercut,
        &this->graphicEngine.getJazzSpecialSprite(JazzSpecialsCodes::Uppercut),
        AnimationState::NotCycle, AnimationState::DefaultSlowdown, shouldFlip);
    return;
  }

  if (newEntityInfo.is_running == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Running,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Running),
        AnimationState::Cycle, AnimationState::DefaultSlowdown, shouldFlip);
    return;

  } else if (newEntityInfo.is_walking == NumericBool::True) {
    if (newEntityInfo.is_intoxicated == NumericBool::True) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::IntoxicatedWalking,
          &this->graphicEngine.getJazzGenericSprite(
              GenericSpriteCodes::IntoxicatedWalking),
          AnimationState::Cycle, AnimationState::DefaultSlowdown, shouldFlip);
    } else {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Walking,
          &this->graphicEngine.getJazzGenericSprite(
              GenericSpriteCodes::Walking),
          AnimationState::Cycle, AnimationState::DefaultSlowdown, shouldFlip);
    }
    return;

  } else if (newEntityInfo.is_falling == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Falling,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Falling),
        AnimationState::Cycle, AnimationState::DefaultSlowdown, shouldFlip);
    return;

  } else if (newEntityInfo.is_jumping == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Jumping,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Jumping),
        AnimationState::NotCycle, AnimationState::DefaultSlowdown, shouldFlip);
    return;
  }

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();

  if (newEntityInfo.is_intoxicated == NumericBool::True && canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::IntoxicatedIdle,
        &this->graphicEngine.getJazzGenericSprite(
            GenericSpriteCodes::IntoxicatedIdle),
        AnimationState::Cycle, AnimationState::DefaultSlowdown, shouldFlip);
    return;

  } else if (canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Idle,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Idle),
        AnimationState::Cycle, AnimationState::DefaultSlowdown, shouldFlip);
    return;
  }
}

void Jazz::update(SnapshotWrapper &snapshot) {
  PlayerDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getPlayerById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "Jazz with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Jazz::getId() const { return this->entityId; }

Jazz::~Jazz() {}
