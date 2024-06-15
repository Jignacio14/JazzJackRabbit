#include "./bullet_gun_1.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct BulletGun1AnimationSpeedCoefs {
  static constexpr double Flying = 25;
  static constexpr double Impact = 25;
};

BulletGun1::BulletGun1(GraphicEngine &graphicEngine, Coordinates &currentCoords,
                       const uint8_t &entityId, SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo(),
      shouldBeDeleted(false), isShowingExitAnimation(false) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GunSpriteCodes::FlyingBullet,
      &this->graphicEngine.getGun1Sprite(GunSpriteCodes::FlyingBullet),
      AnimationState::Cycle, BulletGun1AnimationSpeedCoefs::Flying,
      AnimationState::NotFlip);

  bool foundEntity = snapshot.getBulletById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "BulletGun1 with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void BulletGun1::render(int iterationNumber) {}

void BulletGun1::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void BulletGun1::update(bool isWalking, bool isRunning,
                        std::string movingDirection) {}

void BulletGun1::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void BulletGun1::renderFromLeftCorner(int iterationNumber,
                                      const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void BulletGun1::updateAnimation(const SnapshotWrapper &snapshot,
                                 const BulletDto &newEntityInfo) {}

void BulletGun1::update(SnapshotWrapper &snapshot) {
  BulletDto newEntityInfo;
  bool foundBullet = snapshot.getBulletById(this->entityId, &newEntityInfo);

  if (this->isShowingExitAnimation &&
      this->currentAnimation->canBreakAnimation()) {
    this->shouldBeDeleted = true;
    return;
  } else if (this->isShowingExitAnimation) {
    return;
  }

  if (!foundBullet) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, SfxSpriteCodes::Impact,
        &this->graphicEngine.getSfxSprite(SfxSpriteCodes::Impact),
        AnimationState::NotCycle, BulletGun1AnimationSpeedCoefs::Impact,
        AnimationState::NotFlip);
    this->isShowingExitAnimation = true;
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t BulletGun1::getId() const { return this->entityId; }

bool BulletGun1::shouldDelete() const { return this->shouldBeDeleted; }

BulletGun1::~BulletGun1() {}
