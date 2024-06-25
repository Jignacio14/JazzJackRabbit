#include "./bubba.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct BubbaAnimationSpeedCoefs {
  static constexpr double Death = 5;
  static constexpr double Hurt = 16;
  static constexpr double Idle = 15;
  static constexpr double Shooting = 15;
};

Bubba::Bubba(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
             Coordinates &currentCoords, const uint8_t &entityId,
             SnapshotWrapper &snapshot)
    : entityId(entityId), type(GeneralType::Enemy),
      graphicEngine(graphicEngine), audioEngine(audioEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo(),
      hitbox(HitboxSizes::EnemyWidth, HitboxSizes::EnemyHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, EnemiesGenericSpriteCodes::Idle,
      &this->graphicEngine.getBubbaSprite(EnemiesGenericSpriteCodes::Idle),
      AnimationState::Cycle, BubbaAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity = snapshot.getEnemyById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Bubba with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Bubba::renderFromLeftCorner(int iterationNumber,
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

void Bubba::updateAnimation(const SnapshotWrapper &snapshot,
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
          &this->graphicEngine.getBubbaSprite(EnemiesGenericSpriteCodes::Death),
          AnimationState::Cycle, BubbaAnimationSpeedCoefs::Death, shouldFlip,
          this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playBubbaDeathSound();
      }
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {

    if (this->currentAnimation->getCode() != EnemiesGenericSpriteCodes::Hurt) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Hurt,
          &this->graphicEngine.getBubbaSprite(EnemiesGenericSpriteCodes::Hurt),
          AnimationState::NotCycle, BubbaAnimationSpeedCoefs::Hurt, shouldFlip,
          this->hitbox);

      if (isInCameraFocus) {
        this->audioEngine.playBubbaHurtSound();
      }
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {

    if (this->currentAnimation->getCode() !=
        EnemiesGenericSpriteCodes::Shooting) {

      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Shooting,
          &this->graphicEngine.getBubbaSprite(
              EnemiesGenericSpriteCodes::Shooting),
          AnimationState::NotCycle, BubbaAnimationSpeedCoefs::Shooting,
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
        &this->graphicEngine.getBubbaSprite(EnemiesGenericSpriteCodes::Idle),
        AnimationState::Cycle, BubbaAnimationSpeedCoefs::Idle, shouldFlip,
        this->hitbox);
  }
}

void Bubba::update(SnapshotWrapper &snapshot, const Coordinates &leftCorner) {
  EnemyDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getEnemyById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "Bubba with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time\n";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo, leftCorner);
  this->entityInfo = newEntityInfo;
}

uint8_t Bubba::getId() const { return this->entityId; }

u_int8_t Bubba::getType() const { return this->type; }

Bubba::~Bubba() {}
