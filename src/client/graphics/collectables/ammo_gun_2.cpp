#include "./ammo_gun_2.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

AmmoGun2::AmmoGun2(GraphicEngine &graphicEngine, Coordinates &currentCoords,
                   const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo() {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GunSpriteCodes::CollectableAmmo,
      &this->graphicEngine.getGun2Sprite(GunSpriteCodes::CollectableAmmo),
      AnimationState::Cycle, AnimationState::DefaultSlowdown,
      AnimationState::NotFlip);

  bool foundEntity =
      snapshot.getCollectableById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "AmmoGun2 with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void AmmoGun2::render(int iterationNumber) {}

void AmmoGun2::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void AmmoGun2::update(bool isWalking, bool isRunning,
                      std::string movingDirection) {}

void AmmoGun2::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void AmmoGun2::renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void AmmoGun2::updateAnimation(const SnapshotWrapper &snapshot,
                               const CollectableDto &newEntityInfo) {}

void AmmoGun2::update(SnapshotWrapper &snapshot) {
  CollectableDto newEntityInfo;
  bool foundCollectable =
      snapshot.getCollectableById(this->entityId, &newEntityInfo);
  if (!foundCollectable) {
    // I have to signal destroy here
    std::cerr << "AmmoGun2 with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t AmmoGun2::getId() const { return this->entityId; }

AmmoGun2::~AmmoGun2() {}
