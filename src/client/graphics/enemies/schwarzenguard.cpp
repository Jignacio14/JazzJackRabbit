#include "./schwarzenguard.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct SchwarzenguardAnimationSpeedCoefs {
  static constexpr double Death = 5;
  static constexpr double Hurt = 10;
  static constexpr double Idle = 6;
  static constexpr double Shooting = 15;
};

Schwarzenguard::Schwarzenguard(GraphicEngine &graphicEngine,
                               AudioEngine &audioEngine,
                               Coordinates &currentCoords,
                               const uint8_t &entityId,
                               SnapshotWrapper &snapshot)
    : entityId(entityId), type(GeneralType::Enemy),
      graphicEngine(graphicEngine), audioEngine(audioEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo(),
      hitbox(HitboxSizes::EnemyWidth, HitboxSizes::EnemyHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, EnemiesGenericSpriteCodes::Idle,
      &this->graphicEngine.getSchwarzenguardSprite(
          EnemiesGenericSpriteCodes::Idle),
      AnimationState::Cycle, SchwarzenguardAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity = snapshot.getEnemyById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Schwarzenguard with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Schwarzenguard::renderFromLeftCorner(int iterationNumber,
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

void Schwarzenguard::updateAnimation(const SnapshotWrapper &snapshot,
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
          &this->graphicEngine.getSchwarzenguardSprite(
              EnemiesGenericSpriteCodes::Death),
          AnimationState::NotCycle, SchwarzenguardAnimationSpeedCoefs::Death,
          shouldFlip, this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playSchwarzenguardDeathSound();
      }
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {

    if (this->currentAnimation->getCode() != EnemiesGenericSpriteCodes::Hurt) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Hurt,
          &this->graphicEngine.getSchwarzenguardSprite(
              EnemiesGenericSpriteCodes::Hurt),
          AnimationState::NotCycle, SchwarzenguardAnimationSpeedCoefs::Hurt,
          shouldFlip, this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playSchwarzenguardHurtSound();
      }
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {

    if (this->currentAnimation->getCode() !=
        EnemiesGenericSpriteCodes::Shooting) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Shooting,
          &this->graphicEngine.getSchwarzenguardSprite(
              EnemiesGenericSpriteCodes::Shooting),
          AnimationState::NotCycle, SchwarzenguardAnimationSpeedCoefs::Shooting,
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
        &this->graphicEngine.getSchwarzenguardSprite(
            EnemiesGenericSpriteCodes::Idle),
        AnimationState::Cycle, SchwarzenguardAnimationSpeedCoefs::Idle,
        shouldFlip, this->hitbox);
  }
}

void Schwarzenguard::update(SnapshotWrapper &snapshot,
                            const Coordinates &leftCorner) {
  EnemyDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getEnemyById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "Schwarzenguard with entity id " +
                     std::to_string(this->entityId) +
                     " was not found in snapshot at update time\n";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo, leftCorner);
  this->entityInfo = newEntityInfo;
}

uint8_t Schwarzenguard::getId() const { return this->entityId; }

u_int8_t Schwarzenguard::getType() const { return this->type; }

Schwarzenguard::~Schwarzenguard() {}
