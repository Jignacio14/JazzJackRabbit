#include "./spaz.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct SpazAnimationSpeedCoefs {
  static constexpr double Death = 25;
  static constexpr double Hurt = 25;
  static constexpr double Idle = 35;
  static constexpr double IntoxicatedIdle = 25;
  static constexpr double IntoxicatedWalking = 25;
  static constexpr double Jumping = 25;
  static constexpr double Falling = 25;
  static constexpr double Running = 25;
  static constexpr double Shooting = 25;
  static constexpr double Walking = 25;
  static constexpr double SideKick = 25;
};

Spaz::Spaz(GraphicEngine &graphicEngine, Coordinates &currentCoords,
           const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords),
      isWalkingLeft(false), isWalkingRight(false), isWalkingUp(false),
      isWalkingDown(false), isRunning(false), entityInfo() {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GenericSpriteCodes::Idle,
      &this->graphicEngine.getSpazGenericSprite(GenericSpriteCodes::Idle),
      AnimationState::Cycle, SpazAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip);

  bool foundEntity = snapshot.getPlayerById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Spaz with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

/*void Spaz::debugUpdateLocation(int iterationNumber) {
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

void Spaz::render(int iterationNumber) {
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

void Spaz::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Spaz::update(bool isWalking, bool isRunning, std::string movingDirection) {

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
    this->currentState = &this->graphicEngine.getSpazGenericSprite("idle1");
  } else if (!wasWalking && isNowWalking) {
    this->currentState = &this->graphicEngine.getSpazGenericSprite("walking");
  }*/
}

void Spaz::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Spaz::renderFromLeftCorner(int iterationNumber,
                                const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

Coordinates Spaz::getCoords() { return this->currentCoords; }

void Spaz::setX(int x) { this->currentCoords.setX(x); }

void Spaz::setY(int y) { this->currentCoords.setX(y); }

void Spaz::updateAnimation(const SnapshotWrapper &snapshot,
                           const PlayerDto &newEntityInfo) {

  bool shouldFlip = newEntityInfo.facing_direction == FacingDirectionsIds::Right
                        ? AnimationState::NotFlip
                        : AnimationState::Flip;

  if (newEntityInfo.is_dead == NumericBool::True) {
    if (this->entityInfo.is_dead == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Death,
          &this->graphicEngine.getSpazGenericSprite(GenericSpriteCodes::Death),
          AnimationState::NotCycle, SpazAnimationSpeedCoefs::Death, shouldFlip);
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {
    if (this->entityInfo.was_hurt == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Hurt,
          &this->graphicEngine.getSpazGenericSprite(GenericSpriteCodes::Hurt),
          AnimationState::NotCycle, SpazAnimationSpeedCoefs::Hurt, shouldFlip);
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Shooting,
        &this->graphicEngine.getSpazGenericSprite(GenericSpriteCodes::Shooting),
        AnimationState::NotCycle, SpazAnimationSpeedCoefs::Shooting,
        shouldFlip);
    return;

  } else if (newEntityInfo.shot_special == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, SpazSpecialsCodes::SideKick,
        &this->graphicEngine.getSpazSpecialSprite(SpazSpecialsCodes::SideKick),
        AnimationState::NotCycle, SpazAnimationSpeedCoefs::SideKick,
        shouldFlip);
    return;
  }

  if (newEntityInfo.is_running == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Running,
        &this->graphicEngine.getSpazGenericSprite(GenericSpriteCodes::Running),
        AnimationState::Cycle, SpazAnimationSpeedCoefs::Running, shouldFlip);
    return;

  } else if (newEntityInfo.is_walking == NumericBool::True) {
    if (newEntityInfo.is_intoxicated == NumericBool::True) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::IntoxicatedWalking,
          &this->graphicEngine.getSpazGenericSprite(
              GenericSpriteCodes::IntoxicatedWalking),
          AnimationState::Cycle, SpazAnimationSpeedCoefs::IntoxicatedWalking,
          shouldFlip);
    } else {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Walking,
          &this->graphicEngine.getSpazGenericSprite(
              GenericSpriteCodes::Walking),
          AnimationState::Cycle, SpazAnimationSpeedCoefs::Walking, shouldFlip);
    }
    return;

  } else if (newEntityInfo.is_falling == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Falling,
        &this->graphicEngine.getSpazGenericSprite(GenericSpriteCodes::Falling),
        AnimationState::Cycle, SpazAnimationSpeedCoefs::Falling, shouldFlip);
    return;

  } else if (newEntityInfo.is_jumping == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Jumping,
        &this->graphicEngine.getSpazGenericSprite(GenericSpriteCodes::Jumping),
        AnimationState::NotCycle, SpazAnimationSpeedCoefs::Jumping, shouldFlip);
    return;
  }

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();

  if (newEntityInfo.is_intoxicated == NumericBool::True && canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::IntoxicatedIdle,
        &this->graphicEngine.getSpazGenericSprite(
            GenericSpriteCodes::IntoxicatedIdle),
        AnimationState::Cycle, SpazAnimationSpeedCoefs::IntoxicatedIdle,
        shouldFlip);
    return;

  } else if (canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Idle,
        &this->graphicEngine.getSpazGenericSprite(GenericSpriteCodes::Idle),
        AnimationState::Cycle, SpazAnimationSpeedCoefs::Idle, shouldFlip);
    return;
  }
}

void Spaz::update(SnapshotWrapper &snapshot) {
  PlayerDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getPlayerById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "Spaz with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Spaz::getId() const { return this->entityId; }

Spaz::~Spaz() {}
