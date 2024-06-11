#include "./bullet_gun_2.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

BulletGun2::BulletGun2(GraphicEngine &graphicEngine, Coordinates &currentCoords,
                       const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo() {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GunSpriteCodes::FlyingBullet,
      &this->graphicEngine.getGun1Sprite(GunSpriteCodes::FlyingBullet),
      AnimationState::Cycle, AnimationState::DefaultSlowdown,
      AnimationState::NotFlip);

  bool foundEntity = snapshot.getBulletById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "BulletGun2 with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void BulletGun2::render(int iterationNumber) {}

void BulletGun2::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void BulletGun2::update(bool isWalking, bool isRunning,
                        std::string movingDirection) {}

void BulletGun2::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void BulletGun2::renderFromLeftCorner(int iterationNumber,
                                      const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void BulletGun2::updateAnimation(const SnapshotWrapper &snapshot,
                                 const BulletDto &newEntityInfo) {}

void BulletGun2::update(SnapshotWrapper &snapshot) {
  BulletDto newEntityInfo;
  bool foundCollectable =
      snapshot.getBulletById(this->entityId, &newEntityInfo);
  if (!foundCollectable) {
    // I have to signal destroy here
    std::cerr << "BulletGun2 with entity id " + std::to_string(this->entityId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t BulletGun2::getId() const { return this->entityId; }

BulletGun2::~BulletGun2() {}
