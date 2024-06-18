#include "./lori.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct LoriAnimationSpeedCoefs {
  static constexpr double Death = 25;
  static constexpr double Hurt = 25;
  static constexpr double Idle = 12;
  static constexpr double IntoxicatedIdle = 25;
  static constexpr double IntoxicatedWalking = 25;
  static constexpr double Jumping = 15;
  static constexpr double Falling = 18;
  static constexpr double Running = 25;
  static constexpr double Shooting = 25;
  static constexpr double Walking = 18;
  static constexpr double ShortKick = 25;
};

Lori::Lori(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
           Coordinates &currentCoords, const uint8_t &entityId,
           SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      audioEngine(audioEngine), currentAnimation(nullptr),
      currentCoords(currentCoords), isWalkingLeft(false), isWalkingRight(false),
      isWalkingUp(false), isWalkingDown(false), isRunning(false), entityInfo(),
      hitbox(HitboxSizes::PlayerWidth, HitboxSizes::PlayerHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GenericSpriteCodes::Idle,
      &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Idle),
      AnimationState::Cycle, LoriAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity = snapshot.getPlayerById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Lori with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Lori::render(int iterationNumber) {}

void Lori::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Lori::update(bool isWalking, bool isRunning, std::string movingDirection) {
}

void Lori::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Lori::renderFromLeftCorner(int iterationNumber,
                                const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

Coordinates Lori::getCoords() { return this->currentCoords; }

void Lori::setX(int x) { this->currentCoords.setX(x); }

void Lori::setY(int y) { this->currentCoords.setX(y); }

void Lori::updateAnimation(const SnapshotWrapper &snapshot,
                           const PlayerDto &newEntityInfo) {

  bool shouldFlip = newEntityInfo.facing_direction == FacingDirectionsIds::Right
                        ? AnimationState::NotFlip
                        : AnimationState::Flip;

  if (newEntityInfo.is_dead == NumericBool::True) {
    if (this->entityInfo.is_dead == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Death,
          &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Death),
          AnimationState::NotCycle, LoriAnimationSpeedCoefs::Death, shouldFlip,
          this->hitbox);
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {
    if (this->entityInfo.was_hurt == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Hurt,
          &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Hurt),
          AnimationState::NotCycle, LoriAnimationSpeedCoefs::Hurt, shouldFlip,
          this->hitbox);
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Shooting,
        &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Shooting),
        AnimationState::NotCycle, LoriAnimationSpeedCoefs::Shooting, shouldFlip,
        this->hitbox);
    return;

  } else if (newEntityInfo.shot_special == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, LoriSpecialsCodes::ShortKick,
        &this->graphicEngine.getLoriSpecialSprite(LoriSpecialsCodes::ShortKick),
        AnimationState::NotCycle, LoriAnimationSpeedCoefs::ShortKick,
        shouldFlip, this->hitbox);
    return;
  }

  if (newEntityInfo.is_falling == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Falling,
        &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Falling),
        AnimationState::Cycle, LoriAnimationSpeedCoefs::Falling, shouldFlip,
        this->hitbox);
    return;

  } else if (newEntityInfo.is_jumping == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Jumping,
        &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Jumping),
        AnimationState::NotCycle, LoriAnimationSpeedCoefs::Jumping, shouldFlip,
        this->hitbox);
    return;
  }

  if (newEntityInfo.is_running == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Running,
        &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Running),
        AnimationState::Cycle, LoriAnimationSpeedCoefs::Running, shouldFlip,
        this->hitbox);
    return;

  } else if (newEntityInfo.is_walking == NumericBool::True) {
    if (newEntityInfo.is_intoxicated == NumericBool::True) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::IntoxicatedWalking,
          &this->graphicEngine.getLoriGenericSprite(
              GenericSpriteCodes::IntoxicatedWalking),
          AnimationState::Cycle, LoriAnimationSpeedCoefs::IntoxicatedWalking,
          shouldFlip, this->hitbox);
    } else {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Walking,
          &this->graphicEngine.getLoriGenericSprite(
              GenericSpriteCodes::Walking),
          AnimationState::Cycle, LoriAnimationSpeedCoefs::Walking, shouldFlip,
          this->hitbox);
    }
    return;
  }

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();

  if (newEntityInfo.is_intoxicated == NumericBool::True && canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::IntoxicatedIdle,
        &this->graphicEngine.getLoriGenericSprite(
            GenericSpriteCodes::IntoxicatedIdle),
        AnimationState::Cycle, LoriAnimationSpeedCoefs::IntoxicatedIdle,
        shouldFlip, this->hitbox);
    return;

  } else if (canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Idle,
        &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Idle),
        AnimationState::Cycle, LoriAnimationSpeedCoefs::Idle, shouldFlip,
        this->hitbox);
    return;
  }
}

void Lori::update(SnapshotWrapper &snapshot) {
  PlayerDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getPlayerById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "Lori with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Lori::getId() const { return this->entityId; }

Lori::~Lori() {}
