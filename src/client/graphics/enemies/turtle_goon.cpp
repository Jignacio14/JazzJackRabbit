#include "./turtle_goon.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct TurtleGoonAnimationSpeedCoefs {
  static constexpr double Death = 10;
  static constexpr double Hurt = 6;
  static constexpr double Idle = 10;
  static constexpr double Shooting = 15;
};

TurtleGoon::TurtleGoon(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
                       Coordinates &currentCoords, const uint8_t &entityId,
                       SnapshotWrapper &snapshot)
    : entityId(entityId), type(GeneralType::Enemy),
      graphicEngine(graphicEngine), audioEngine(audioEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo(),
      hitbox(HitboxSizes::EnemyWidth, HitboxSizes::EnemyHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, EnemiesGenericSpriteCodes::Idle,
      &this->graphicEngine.getTurtleGoonSprite(EnemiesGenericSpriteCodes::Idle),
      AnimationState::Cycle, TurtleGoonAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity = snapshot.getEnemyById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "TurtleGoon with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void TurtleGoon::renderFromLeftCorner(int iterationNumber,
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

void TurtleGoon::updateAnimation(const SnapshotWrapper &snapshot,
                                 const EnemyDto &newEntityInfo,
                                 const Coordinates &leftCorner) {

  bool shouldFlip = newEntityInfo.facing_direction == FacingDirectionsIds::Right
                        ? AnimationState::NotFlip
                        : AnimationState::Flip;

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();
  bool isInCameraFocus = this->graphicEngine.isInCameraFocus(
      leftCorner,
      Coordinates(this->entityInfo.position_x, this->entityInfo.position_y));

  if (this->entityInfo.is_dead == NumericBool::True &&
      newEntityInfo.is_dead == NumericBool::False) {
    canBreakAnimation = true;
  }

  if (newEntityInfo.is_dead == NumericBool::True) {

    if (this->currentAnimation->getCode() != EnemiesGenericSpriteCodes::Death) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Death,
          &this->graphicEngine.getTurtleGoonSprite(
              EnemiesGenericSpriteCodes::Death),
          AnimationState::NotCycle, TurtleGoonAnimationSpeedCoefs::Death,
          shouldFlip, this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playTurtleGoonDeathSound();
      }
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {

    if (this->currentAnimation->getCode() != EnemiesGenericSpriteCodes::Hurt) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Hurt,
          &this->graphicEngine.getTurtleGoonSprite(
              EnemiesGenericSpriteCodes::Hurt),
          AnimationState::NotCycle, TurtleGoonAnimationSpeedCoefs::Hurt,
          shouldFlip, this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playTurtleGoonHurtSound();
      }
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {

    if (this->currentAnimation->getCode() !=
        EnemiesGenericSpriteCodes::Shooting) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Shooting,
          &this->graphicEngine.getTurtleGoonSprite(
              EnemiesGenericSpriteCodes::Shooting),
          AnimationState::NotCycle, TurtleGoonAnimationSpeedCoefs::Shooting,
          shouldFlip, this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playGenericEnemyMeleeShotSound();
      }
    }
    return;
  }

  if (this->currentAnimation->getCode() != EnemiesGenericSpriteCodes::Idle &&
      canBreakAnimation) {

    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, EnemiesGenericSpriteCodes::Idle,
        &this->graphicEngine.getTurtleGoonSprite(
            EnemiesGenericSpriteCodes::Idle),
        AnimationState::Cycle, TurtleGoonAnimationSpeedCoefs::Idle, shouldFlip,
        this->hitbox);
  }
}

void TurtleGoon::update(SnapshotWrapper &snapshot,
                        const Coordinates &leftCorner) {
  EnemyDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getEnemyById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "TurtleGoon with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time\n";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo, leftCorner);
  this->entityInfo = newEntityInfo;
}

uint8_t TurtleGoon::getId() const { return this->entityId; }

u_int8_t TurtleGoon::getType() const { return this->type; }

TurtleGoon::~TurtleGoon() {}
