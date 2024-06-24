#include "./ammo_gun_2.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct AmmoGun2AnimationSpeedCoefs {
  static constexpr double Idle = 15;
  static constexpr double Shine = 2;
};

AmmoGun2::AmmoGun2(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
                   Coordinates &currentCoords, const uint8_t &entityId,
                   SnapshotWrapper &snapshot)
    : entityId(entityId), type(GeneralType::Collectable),
      graphicEngine(graphicEngine), audioEngine(audioEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo(),
      shouldBeDeleted(false), isShowingExitAnimation(false),
      hitbox(HitboxSizes::CollectableWidth, HitboxSizes::CollectableHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, GunSpriteCodes::CollectableAmmo,
      &this->graphicEngine.getGun2Sprite(GunSpriteCodes::CollectableAmmo),
      AnimationState::Cycle, AmmoGun2AnimationSpeedCoefs::Idle,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity =
      snapshot.getCollectableById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "AmmoGun2 with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void AmmoGun2::renderFromLeftCorner(int iterationNumber,
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

void AmmoGun2::updateAnimation(const SnapshotWrapper &snapshot,
                               const CollectableDto &newEntityInfo) {}

void AmmoGun2::update(SnapshotWrapper &snapshot,
                      const Coordinates &leftCorner) {
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
        AnimationState::NotCycle, AmmoGun2AnimationSpeedCoefs::Shine,
        AnimationState::NotFlip, this->hitbox);
    this->isShowingExitAnimation = true;

    bool isInCameraFocus =
        this->graphicEngine.isInCameraFocus(leftCorner, this->currentCoords);

    if (isInCameraFocus) {
      this->audioEngine.playAmmoCollectedSound();
    }
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t AmmoGun2::getId() const { return this->entityId; }

u_int8_t AmmoGun2::getType() const { return this->type; }

bool AmmoGun2::shouldDelete() const { return this->shouldBeDeleted; }

AmmoGun2::~AmmoGun2() {}
