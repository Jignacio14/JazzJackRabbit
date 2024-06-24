#include "./lori.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../../disconnection_exception.h"
#include "../sprite_props.h"
#include <unordered_map>

struct LoriAnimationSpeedCoefs {
  static constexpr double Death = 13;
  static constexpr double Hurt = 15;
  static constexpr double Idle = 12;
  static constexpr double IntoxicatedIdle = 15;
  static constexpr double IntoxicatedWalking = 25;
  static constexpr double Jumping = 15;
  static constexpr double Falling = 18;
  static constexpr double Running = 18;
  static constexpr double Shooting = 15;
  static constexpr double Walking = 18;
  static constexpr double ShortKick = 25;
};

Lori::Lori(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
           Coordinates &currentCoords, const uint8_t &entityId,
           SnapshotWrapper &snapshot)
    : entityId(entityId), type(GeneralType::Player),
      graphicEngine(graphicEngine), audioEngine(audioEngine),
      currentAnimation(nullptr), currentCoords(currentCoords),
      isWalkingLeft(false), isWalkingRight(false), isWalkingUp(false),
      isWalkingDown(false), isRunning(false), entityInfo(),
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

void Lori::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Lori::renderFromLeftCorner(int iterationNumber,
                                const Coordinates &leftCorner) {
  bool isInCameraFocus =
      this->graphicEngine.isInCameraFocus(leftCorner, this->currentCoords);
  if (isInCameraFocus) {
    this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                                 this->currentCoords);
  } else {
    this->currentAnimation->advanceWithoutRendering(iterationNumber);
  }
}

Coordinates Lori::getCoords() { return this->currentCoords; }

void Lori::setX(int x) { this->currentCoords.setX(x); }

void Lori::setY(int y) { this->currentCoords.setX(y); }

void Lori::updateAnimation(const SnapshotWrapper &snapshot,
                           const PlayerDto &newEntityInfo,
                           const Coordinates &leftCorner) {

  bool shouldFlip = newEntityInfo.facing_direction == FacingDirectionsIds::Right
                        ? AnimationState::NotFlip
                        : AnimationState::Flip;

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();
  bool isInCameraFocus =
      this->graphicEngine.isInCameraFocus(leftCorner, this->currentCoords);

  if (this->entityInfo.is_dead == NumericBool::True &&
      newEntityInfo.is_dead == NumericBool::False) {
    canBreakAnimation = true;
  }

  if (newEntityInfo.is_dead == NumericBool::True) {

    if (this->currentAnimation->getCode() != GenericSpriteCodes::Death) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Death,
          &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Death),
          AnimationState::NotCycle, LoriAnimationSpeedCoefs::Death, shouldFlip,
          this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playLoriDeathSound();
      }
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {

    if (this->currentAnimation->getCode() != GenericSpriteCodes::Hurt) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Hurt,
          &this->graphicEngine.getLoriGenericSprite(GenericSpriteCodes::Hurt),
          AnimationState::NotCycle, LoriAnimationSpeedCoefs::Hurt, shouldFlip,
          this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playLorihurtSound();
      }
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {

    if (this->currentAnimation->getCode() != GenericSpriteCodes::Shooting) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Shooting,
          &this->graphicEngine.getLoriGenericSprite(
              GenericSpriteCodes::Shooting),
          AnimationState::NotCycle, LoriAnimationSpeedCoefs::Shooting,
          shouldFlip, this->hitbox);
    }
    return;

  } else if (newEntityInfo.shot_special == NumericBool::True) {

    if (this->currentAnimation->getCode() !=
        LoriAnimationSpeedCoefs::ShortKick) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, LoriSpecialsCodes::ShortKick,
          &this->graphicEngine.getLoriSpecialSprite(
              LoriSpecialsCodes::ShortKick),
          AnimationState::NotCycle, LoriAnimationSpeedCoefs::ShortKick,
          shouldFlip, this->hitbox);
    }
    return;
  }

  if (this->currentAnimation->getCode() == GenericSpriteCodes::Falling &&
      newEntityInfo.is_falling == NumericBool::False) {
    if (isInCameraFocus) {
      this->audioEngine.playGroundHitSound();
    }
  }

  if (newEntityInfo.is_falling == NumericBool::True && canBreakAnimation) {

    if (this->currentAnimation->getCode() != GenericSpriteCodes::Falling) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Falling,
          &this->graphicEngine.getLoriGenericSprite(
              GenericSpriteCodes::Falling),
          AnimationState::Cycle, LoriAnimationSpeedCoefs::Falling, shouldFlip,
          this->hitbox);
    }

    return;

  } else if (newEntityInfo.is_jumping == NumericBool::True &&
             canBreakAnimation) {

    if (this->currentAnimation->getCode() != GenericSpriteCodes::Jumping) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Jumping,
          &this->graphicEngine.getLoriGenericSprite(
              GenericSpriteCodes::Jumping),
          AnimationState::NotCycle, LoriAnimationSpeedCoefs::Jumping,
          shouldFlip, this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playJumpSound();
      }
    }

    return;
  }

  if (newEntityInfo.is_running == NumericBool::True) {

    if (this->currentAnimation->getCode() != GenericSpriteCodes::Running) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, GenericSpriteCodes::Running,
          &this->graphicEngine.getLoriGenericSprite(
              GenericSpriteCodes::Running),
          AnimationState::Cycle, LoriAnimationSpeedCoefs::Running, shouldFlip,
          this->hitbox);
    }
    return;

  } else if (newEntityInfo.is_walking == NumericBool::True &&
             canBreakAnimation) {

    if (this->currentAnimation->getCode() != GenericSpriteCodes::Walking) {

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
    } else if (newEntityInfo.is_intoxicated !=
               this->entityInfo.is_intoxicated) {

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
    }
    return;
  }

  if (this->currentAnimation->getCode() != GenericSpriteCodes::Idle) {

    if (newEntityInfo.is_intoxicated == NumericBool::True &&
        canBreakAnimation) {

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
  } else if (newEntityInfo.is_intoxicated != this->entityInfo.is_intoxicated) {

    if (newEntityInfo.is_intoxicated == NumericBool::True &&
        canBreakAnimation) {

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
}

void Lori::update(SnapshotWrapper &snapshot, const Coordinates &leftCorner) {
  PlayerDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getPlayerById(this->entityId, &newEntityInfo);

  if (!foundPlayableCharacter) {
    throw DisconnectionException(__LINE__, __FILE__);
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo, leftCorner);
  this->entityInfo = newEntityInfo;
}

uint8_t Lori::getId() const { return this->entityId; }

u_int8_t Lori::getType() const { return this->type; }

Lori::~Lori() {}
