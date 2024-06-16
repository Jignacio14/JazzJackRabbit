#include "./turtle_goon.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct TurtleGoonAnimationSpeedCoefs {
  static constexpr double Death = 25;
  static constexpr double Hurt = 25;
  static constexpr double Idle = 35;
  static constexpr double Shooting = 25;
};

TurtleGoon::TurtleGoon(GraphicEngine &graphicEngine, Coordinates &currentCoords,
                       const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
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

void TurtleGoon::render(int iterationNumber) {}

void TurtleGoon::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void TurtleGoon::update(bool isWalking, bool isRunning,
                        std::string movingDirection) {}

void TurtleGoon::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void TurtleGoon::renderFromLeftCorner(int iterationNumber,
                                      const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void TurtleGoon::updateAnimation(const SnapshotWrapper &snapshot,
                                 const EnemyDto &newEntityInfo) {

  bool shouldFlip = newEntityInfo.facing_direction == FacingDirectionsIds::Right
                        ? AnimationState::NotFlip
                        : AnimationState::Flip;

  if (newEntityInfo.is_dead == NumericBool::True) {
    if (this->entityInfo.is_dead == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Death,
          &this->graphicEngine.getTurtleGoonSprite(
              EnemiesGenericSpriteCodes::Death),
          AnimationState::NotCycle, TurtleGoonAnimationSpeedCoefs::Death,
          shouldFlip, this->hitbox);
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {
    if (this->entityInfo.was_hurt == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Hurt,
          &this->graphicEngine.getTurtleGoonSprite(
              EnemiesGenericSpriteCodes::Hurt),
          AnimationState::NotCycle, TurtleGoonAnimationSpeedCoefs::Hurt,
          shouldFlip, this->hitbox);
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, EnemiesGenericSpriteCodes::Shooting,
        &this->graphicEngine.getTurtleGoonSprite(
            EnemiesGenericSpriteCodes::Shooting),
        AnimationState::NotCycle, TurtleGoonAnimationSpeedCoefs::Shooting,
        shouldFlip, this->hitbox);
    return;
  }

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();

  if (canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, EnemiesGenericSpriteCodes::Idle,
        &this->graphicEngine.getTurtleGoonSprite(
            EnemiesGenericSpriteCodes::Idle),
        AnimationState::Cycle, TurtleGoonAnimationSpeedCoefs::Idle, shouldFlip,
        this->hitbox);
    return;
  }
}

void TurtleGoon::update(SnapshotWrapper &snapshot) {
  EnemyDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getEnemyById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "TurtleGoon with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t TurtleGoon::getId() const { return this->entityId; }

TurtleGoon::~TurtleGoon() {}
