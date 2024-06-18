#include "./bubba.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct BubbaAnimationSpeedCoefs {
  static constexpr double Death = 25;
  static constexpr double Hurt = 25;
  static constexpr double Idle = 35;
  static constexpr double Shooting = 25;
};

Bubba::Bubba(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
             Coordinates &currentCoords, const uint8_t &entityId,
             SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      audioEngine(audioEngine), currentAnimation(nullptr),
      currentCoords(currentCoords), entityInfo(),
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

void Bubba::render(int iterationNumber) {}

void Bubba::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Bubba::update(bool isWalking, bool isRunning,
                   std::string movingDirection) {}

void Bubba::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Bubba::renderFromLeftCorner(int iterationNumber,
                                 const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void Bubba::updateAnimation(const SnapshotWrapper &snapshot,
                            const EnemyDto &newEntityInfo) {

  bool shouldFlip = newEntityInfo.facing_direction == FacingDirectionsIds::Right
                        ? AnimationState::NotFlip
                        : AnimationState::Flip;

  if (newEntityInfo.is_dead == NumericBool::True) {
    if (this->entityInfo.is_dead == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Death,
          &this->graphicEngine.getBubbaSprite(EnemiesGenericSpriteCodes::Death),
          AnimationState::NotCycle, BubbaAnimationSpeedCoefs::Death, shouldFlip,
          this->hitbox);
    }
    return;
  }

  if (newEntityInfo.was_hurt == NumericBool::True) {
    if (this->entityInfo.was_hurt == NumericBool::False) {
      this->currentAnimation = std::make_unique<AnimationState>(
          this->graphicEngine, EnemiesGenericSpriteCodes::Hurt,
          &this->graphicEngine.getBubbaSprite(EnemiesGenericSpriteCodes::Hurt),
          AnimationState::NotCycle, BubbaAnimationSpeedCoefs::Hurt, shouldFlip,
          this->hitbox);
    }
    return;
  }

  if (newEntityInfo.shot == NumericBool::True) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, EnemiesGenericSpriteCodes::Shooting,
        &this->graphicEngine.getBubbaSprite(
            EnemiesGenericSpriteCodes::Shooting),
        AnimationState::NotCycle, BubbaAnimationSpeedCoefs::Shooting,
        shouldFlip, this->hitbox);
    return;
  }

  bool canBreakAnimation = this->currentAnimation->canBreakAnimation();

  if (canBreakAnimation) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, EnemiesGenericSpriteCodes::Idle,
        &this->graphicEngine.getBubbaSprite(EnemiesGenericSpriteCodes::Idle),
        AnimationState::Cycle, BubbaAnimationSpeedCoefs::Idle, shouldFlip,
        this->hitbox);
    return;
  }
}

void Bubba::update(SnapshotWrapper &snapshot) {
  EnemyDto newEntityInfo;
  bool foundPlayableCharacter =
      snapshot.getEnemyById(this->entityId, &newEntityInfo);
  if (!foundPlayableCharacter) {
    std::cerr << "Bubba with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Bubba::getId() const { return this->entityId; }

Bubba::~Bubba() {}
