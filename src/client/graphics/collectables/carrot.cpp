#include "./carrot.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct CarrotAnimationSpeedCoefs {
  static constexpr double Idle = 25;
};

Carrot::Carrot(GraphicEngine &graphicEngine, Coordinates &currentCoords,
               const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo() {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, CollectablesSpriteCodes::Carrot,
      &this->graphicEngine.getCollectableSprite(
          CollectablesSpriteCodes::Carrot),
      AnimationState::Cycle, CarrotAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip);

  bool foundEntity =
      snapshot.getCollectableById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Carrot with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Carrot::render(int iterationNumber) {}

void Carrot::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Carrot::update(bool isWalking, bool isRunning,
                    std::string movingDirection) {}

void Carrot::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Carrot::renderFromLeftCorner(int iterationNumber,
                                  const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void Carrot::updateAnimation(const SnapshotWrapper &snapshot,
                             const CollectableDto &newEntityInfo) {}

void Carrot::update(SnapshotWrapper &snapshot) {
  CollectableDto newEntityInfo;
  bool foundCollectable =
      snapshot.getCollectableById(this->entityId, &newEntityInfo);
  if (!foundCollectable) {
    // I have to signal destroy here
    std::cerr << "Carrot with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Carrot::getId() const { return this->entityId; }

Carrot::~Carrot() {}
