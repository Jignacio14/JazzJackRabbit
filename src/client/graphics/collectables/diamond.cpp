#include "./diamond.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct DiamondAnimationSpeedCoefs {
  static constexpr double Idle = 25;
  static constexpr double Shine = 25;
};

Diamond::Diamond(GraphicEngine &graphicEngine, Coordinates &currentCoords,
                 const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo(),
      shouldBeDeleted(false), isShowingExitAnimation(false) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, CollectablesSpriteCodes::Diamond,
      &this->graphicEngine.getCollectableSprite(
          CollectablesSpriteCodes::Diamond),
      AnimationState::Cycle, DiamondAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip);

  bool foundEntity =
      snapshot.getCollectableById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Diamond with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Diamond::render(int iterationNumber) {}

void Diamond::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Diamond::update(bool isWalking, bool isRunning,
                     std::string movingDirection) {}

void Diamond::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Diamond::renderFromLeftCorner(int iterationNumber,
                                   const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void Diamond::updateAnimation(const SnapshotWrapper &snapshot,
                              const CollectableDto &newEntityInfo) {}

void Diamond::update(SnapshotWrapper &snapshot) {
  CollectableDto newEntityInfo;
  bool foundCollectable =
      snapshot.getCollectableById(this->entityId, &newEntityInfo);

  if (this->isShowingExitAnimation &&
      this->currentAnimation->canBreakAnimation()) {
    this->shouldBeDeleted = true;
    return;
  } else if (this->isShowingExitAnimation) {
    return;
  }

  if (!foundCollectable) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, SfxSpriteCodes::Shine,
        &this->graphicEngine.getSfxSprite(SfxSpriteCodes::Shine),
        AnimationState::NotCycle, DiamondAnimationSpeedCoefs::Shine,
        AnimationState::NotFlip);
    this->isShowingExitAnimation = true;
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Diamond::getId() const { return this->entityId; }

bool Diamond::shouldDelete() const { return this->shouldBeDeleted; }

Diamond::~Diamond() {}
