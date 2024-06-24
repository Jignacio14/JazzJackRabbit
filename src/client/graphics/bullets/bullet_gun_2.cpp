#include "./bullet_gun_2.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct BulletGun2AnimationSpeedCoefs {
  static constexpr double Flying = 25;
  static constexpr double Impact = 25;
};

BulletGun2::BulletGun2(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
                       Coordinates &currentCoords, const uint8_t &entityId,
                       SnapshotWrapper &snapshot)
    : entityId(entityId), type(GeneralType::Bullet),
      graphicEngine(graphicEngine), audioEngine(audioEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo(),
      shouldBeDeleted(false), isShowingExitAnimation(false), wasJustShot(true),
      hitbox(HitboxSizes::BulletWidth, HitboxSizes::BulletHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GunSpriteCodes::FlyingBullet,
      &this->graphicEngine.getGun2Sprite(GunSpriteCodes::FlyingBullet),
      AnimationState::Cycle, BulletGun2AnimationSpeedCoefs::Flying,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity = snapshot.getBulletById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "BulletGun2 with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
  this->audioEngine.playGun2ShotSound();
}

void BulletGun2::renderFromLeftCorner(int iterationNumber,
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

void BulletGun2::update(SnapshotWrapper &snapshot,
                        const Coordinates &leftCorner) {

  bool isInCameraFocus =
      this->graphicEngine.isInCameraFocus(leftCorner, this->currentCoords);

  if (isInCameraFocus && this->wasJustShot) {
    this->audioEngine.playGun2ShotSound();
    this->wasJustShot = false;
  }

  if (this->isShowingExitAnimation &&
      this->currentAnimation->canBreakAnimation()) {
    this->shouldBeDeleted = true;
    return;
  } else if (this->isShowingExitAnimation) {
    return;
  }

  BulletDto newEntityInfo;
  bool foundBullet = snapshot.getBulletById(this->entityId, &newEntityInfo);

  if (!foundBullet) {
    this->currentAnimation = std::make_unique<AnimationState>(
        this->graphicEngine, SfxSpriteCodes::Impact,
        &this->graphicEngine.getSfxSprite(SfxSpriteCodes::Impact),
        AnimationState::NotCycle, BulletGun2AnimationSpeedCoefs::Impact,
        AnimationState::NotFlip, this->hitbox);
    this->isShowingExitAnimation = true;

    if (isInCameraFocus) {
      this->audioEngine.playBulletImpactSound();
    }
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);
  this->entityInfo = newEntityInfo;
}

uint8_t BulletGun2::getId() const { return this->entityId; }

u_int8_t BulletGun2::getType() const { return this->type; }

bool BulletGun2::shouldDelete() const { return this->shouldBeDeleted; }

BulletGun2::~BulletGun2() {}
