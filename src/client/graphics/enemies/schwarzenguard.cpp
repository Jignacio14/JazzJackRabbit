#include "./schwarzenguard.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct SchwarzenguardAnimationSpeedCoefs {
  static constexpr double Death = 25;
  static constexpr double Hurt = 25;
  static constexpr double Idle = 35;
  static constexpr double Shooting = 25;
};

Schwarzenguard::Schwarzenguard(GraphicEngine &graphicEngine,
                               Coordinates &currentCoords,
                               const uint8_t &entityId,
                               SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo() {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, EnemiesGenericSpriteCodes::Idle,
      &this->graphicEngine.getSchwarzenguardSprite(
          EnemiesGenericSpriteCodes::Idle),
      AnimationState::Cycle, SchwarzenguardAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip);

  bool foundEntity = snapshot.getEnemyById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Schwarzenguard with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Schwarzenguard::render(int iterationNumber) {}

void Schwarzenguard::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Schwarzenguard::update(bool isWalking, bool isRunning,
                            std::string movingDirection) {}

void Schwarzenguard::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Schwarzenguard::renderFromLeftCorner(int iterationNumber,
                                          const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void Schwarzenguard::updateAnimation(const SnapshotWrapper &snapshot,
                                     const EnemyDto &newEntityInfo) {

  bool shouldFlip = newEntityInfo.facing_direction == FacingDirectionsIds::Right
                        ? AnimationState::NotFlip
                        : AnimationState::Flip;

  if (newEntityInfo.is_dead == NumericBool::True) {
    if (this->entityInfo.is_dead == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Death,
          &this->graphicEngine.getSchwarzenguardSprite(
              EnemiesGenericSpriteCodes::Death),
          AnimationState::NotCycle, SchwarzenguardAnimationSpeedCoefs::Death,
          shouldFlip);
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {
    if (this->entityInfo.was_hurt == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Hurt,
          &this->graphicEngine.getSchwarzenguardSprite(
              EnemiesGenericSpriteCodes::Hurt),
          AnimationState::NotCycle, SchwarzenguardAnimationSpeedCoefs::Hurt,
          shouldFlip);
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, EnemiesGenericSpriteCodes::Shooting,
        &this->graphicEngine.getSchwarzenguardSprite(
            EnemiesGenericSpriteCodes::Shooting),
        AnimationState::NotCycle, SchwarzenguardAnimationSpeedCoefs::Shooting,
        shouldFlip);
    return;
  }

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();

  if (canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, EnemiesGenericSpriteCodes::Idle,
        &this->graphicEngine.getSchwarzenguardSprite(
            EnemiesGenericSpriteCodes::Idle),
        AnimationState::Cycle, SchwarzenguardAnimationSpeedCoefs::Idle,
        shouldFlip);
    return;
  }
}

void Schwarzenguard::update(SnapshotWrapper &snapshot) {
  EnemyDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getEnemyById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "Schwarzenguard with entity id " +
                     std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Schwarzenguard::getId() const { return this->entityId; }

Schwarzenguard::~Schwarzenguard() {}
