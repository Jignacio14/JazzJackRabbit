#include "./coin.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct CoinAnimationSpeedCoefs {
  static constexpr double Idle = 12;
  static constexpr double Shine = 2;
};

Coin::Coin(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
           Coordinates &currentCoords, const uint8_t &entityId,
           SnapshotWrapper &snapshot)
    : entityId(entityId), type(GeneralType::Collectable),
      graphicEngine(graphicEngine), audioEngine(audioEngine),
      currentAnimation(nullptr), currentCoords(currentCoords), entityInfo(),
      shouldBeDeleted(false), isShowingExitAnimation(false),
      hitbox(HitboxSizes::CollectableWidth, HitboxSizes::CollectableHeight) {

  this->currentAnimation = std::make_unique<AnimationState>(
      this->graphicEngine, CollectablesSpriteCodes::Coin,
      &this->graphicEngine.getCollectableSprite(CollectablesSpriteCodes::Coin),
      AnimationState::Cycle, CoinAnimationSpeedCoefs::Idle,
      AnimationState::NotFlip, this->hitbox);

  bool foundEntity =
      snapshot.getCollectableById(this->entityId, &this->entityInfo);
  if (!foundEntity) {
    std::string errorMessage = "Coin with id " +
                               std::to_string(this->entityId) +
                               " was not found in the initialization snapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

void Coin::renderFromLeftCorner(int iterationNumber,
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

void Coin::updateAnimation(const SnapshotWrapper &snapshot,
                           const CollectableDto &newEntityInfo) {}

void Coin::update(SnapshotWrapper &snapshot, const Coordinates &leftCorner) {
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
        AnimationState::NotCycle, CoinAnimationSpeedCoefs::Shine,
        AnimationState::NotFlip, this->hitbox);
    this->isShowingExitAnimation = true;

    bool isInCameraFocus =
        this->graphicEngine.isInCameraFocus(leftCorner, this->currentCoords);

    if (isInCameraFocus) {
      this->audioEngine.playCoinCollectedSound();
    }
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Coin::getId() const { return this->entityId; }

u_int8_t Coin::getType() const { return this->type; }

bool Coin::shouldDelete() const { return this->shouldBeDeleted; }

Coin::~Coin() {}
