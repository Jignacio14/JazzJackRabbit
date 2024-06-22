#include "./diamond.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct DiamondAnimationSpeedCoefs {
  static constexpr double Idle = 10;
  static constexpr double Shine = 2;
};

Diamond::Diamond(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
                 Coordinates &currentCoords, const uint8_t &entityId,
                 SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      audioEngine(audioEngine), currentAnimation(nullptr),
      currentCoords(currentCoords), entityInfo(), shouldBeDeleted(false),
      isShowingExitAnimation(false),
      hitbox(HitboxSizes::CollectableWidth, HitboxSizes::CollectableHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, CollectablesSpriteCodes::Diamond,
      &this->graphicEngine.getCollectableSprite(
          CollectablesSpriteCodes::Diamond),
      AnimationState::Cycle, DiamondAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity =
      snapshot.getCollectableById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Diamond with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Diamond::renderFromLeftCorner(int iterationNumber,
                                   const Coordinates &leftCorner) {
  bool isInCameraFocus =
      this->graphicEngine.isInCameraFocus(leftCorner, this->currentCoords);
  if (isInCameraFocus) {
    this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                                 this->currentCoords);
  }
}

void Diamond::updateAnimation(const SnapshotWrapper &snapshot,
                              const CollectableDto &newEntityInfo) {}

void Diamond::update(SnapshotWrapper &snapshot, const Coordinates &leftCorner) {
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
        AnimationState::NotFlip, this->hitbox);
    this->isShowingExitAnimation = true;

    bool isInCameraFocus =
        this->graphicEngine.isInCameraFocus(leftCorner, this->currentCoords);

    if (isInCameraFocus) {
      this->audioEngine.playDiamondCollectedSound();
    }
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
