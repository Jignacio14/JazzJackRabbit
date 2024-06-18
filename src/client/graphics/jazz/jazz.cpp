#include "./jazz.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

#include "../../../common/global_configs.h"

struct JazzAnimationSpeedCoefs {
  static constexpr double Death = 25;
  static constexpr double Hurt = 25;
  static constexpr double Idle = 15;
  static constexpr double IntoxicatedIdle = 25;
  static constexpr double IntoxicatedWalking = 25;
  static constexpr double Jumping = 15;
  static constexpr double Falling = 20;
  static constexpr double Running = 25;
  static constexpr double Shooting = 25;
  static constexpr double Walking = 17;
  static constexpr double Uppercut = 25;
};

Jazz::Jazz(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
           Coordinates &currentCoords, const uint8_t &entityId,
           SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      audioEngine(audioEngine), currentAnimation(nullptr),
      currentSound(nullptr), currentCoords(currentCoords), isWalkingLeft(false),
      isWalkingRight(false), isWalkingUp(false), isWalkingDown(false),
      isRunning(false), entityInfo(),
      hitbox(HitboxSizes::PlayerWidth, HitboxSizes::PlayerHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GenericSpriteCodes::Idle,
      &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Idle),
      AnimationState::Cycle, JazzAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity = snapshot.getPlayerById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Jazz with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Jazz::render(int iterationNumber) {}

void Jazz::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Jazz::update(bool isWalking, bool isRunning, std::string movingDirection) {
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
          AnimationState::NotCycle, JazzAnimationSpeedCoefs::Death, shouldFlip,
          this->hitbox);
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {
    if (this->entityInfo.was_hurt == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Hurt,
          &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Hurt),
          AnimationState::NotCycle, JazzAnimationSpeedCoefs::Hurt, shouldFlip,
          this->hitbox);
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {

    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Shooting,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Shooting),
        AnimationState::NotCycle, JazzAnimationSpeedCoefs::Shooting, shouldFlip,
        this->hitbox);
    return;

  } else if (newEntityInfo.shot_special == NumericBool::True) {

    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, JazzSpecialsCodes::Uppercut,
        &this->graphicEngine.getJazzSpecialSprite(JazzSpecialsCodes::Uppercut),
        AnimationState::NotCycle, JazzAnimationSpeedCoefs::Uppercut, shouldFlip,
        this->hitbox);
    return;
  }

  if (newEntityInfo.is_falling == NumericBool::True) {

    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Falling,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Falling),
        AnimationState::Cycle, JazzAnimationSpeedCoefs::Falling, shouldFlip,
        this->hitbox);
    return;

  } else if (newEntityInfo.is_jumping == NumericBool::True) {

    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Jumping,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Jumping),
        AnimationState::NotCycle, JazzAnimationSpeedCoefs::Jumping, shouldFlip,
        this->hitbox);

    if (this->entityInfo.is_jumping == NumericBool::False) {
      /* this->currentSound = std::make_unique<SoundEffect>(
           this->audioEngine.getSdlMixerReference(),
           this->audioEngine.getSound());
       this->currentSound->play();*/
      this->audioEngine.playSound();
    }

    return;
  }

  if (newEntityInfo.is_running == NumericBool::True) {

    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Running,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Running),
        AnimationState::Cycle, JazzAnimationSpeedCoefs::Running, shouldFlip,
        this->hitbox);
    return;

  } else if (newEntityInfo.is_walking == NumericBool::True) {

    if (newEntityInfo.is_intoxicated == NumericBool::True) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::IntoxicatedWalking,
          &this->graphicEngine.getJazzGenericSprite(
              GenericSpriteCodes::IntoxicatedWalking),
          AnimationState::Cycle, JazzAnimationSpeedCoefs::IntoxicatedWalking,
          shouldFlip, this->hitbox);
    } else {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Walking,
          &this->graphicEngine.getJazzGenericSprite(
              GenericSpriteCodes::Walking),
          AnimationState::Cycle, JazzAnimationSpeedCoefs::Walking, shouldFlip,
          this->hitbox);
    }
    return;
  }

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();

  if (newEntityInfo.is_intoxicated == NumericBool::True && canBreakAnimation) {

    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::IntoxicatedIdle,
        &this->graphicEngine.getJazzGenericSprite(
            GenericSpriteCodes::IntoxicatedIdle),
        AnimationState::Cycle, JazzAnimationSpeedCoefs::IntoxicatedIdle,
        shouldFlip, this->hitbox);
    return;

  } else if (canBreakAnimation) {

    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, GenericSpriteCodes::Idle,
        &this->graphicEngine.getJazzGenericSprite(GenericSpriteCodes::Idle),
        AnimationState::Cycle, JazzAnimationSpeedCoefs::Idle, shouldFlip,
        this->hitbox);
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
