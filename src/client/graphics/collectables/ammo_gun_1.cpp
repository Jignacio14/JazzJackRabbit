#include "./ammo_gun_1.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

AmmoGun1::AmmoGun1(GraphicEngine &graphicEngine, Coordinates &currentCoords,
                   const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo() {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GunSpriteCodes::CollectableAmmo,
      &this->graphicEngine.getGun1Sprite(GunSpriteCodes::CollectableAmmo),
      AnimationState::Cycle, AnimationState::DefaultSlowdown,
      AnimationState::NotFlip);

  bool foundEntity =
      snapshot.getCollectableById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "AmmoGun1 with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void AmmoGun1::render(int iterationNumber) {}

void AmmoGun1::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void AmmoGun1::update(bool isWalking, bool isRunning,
                      std::string movingDirection) {}

void AmmoGun1::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void AmmoGun1::renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void AmmoGun1::updateAnimation(const SnapshotWrapper &snapshot,
                               const CollectableDto &newEntityInfo) {}

void AmmoGun1::update(SnapshotWrapper &snapshot) {
  CollectableDto newEntityInfo;
  bool foundCollectable =
      snapshot.getCollectableById(this->entityId, &newEntityInfo);
  if (!foundCollectable) {
    // I have to signal destroy here
    std::cerr << "AmmoGun1 with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t AmmoGun1::getId() const { return this->entityId; }

AmmoGun1::~AmmoGun1() {}
