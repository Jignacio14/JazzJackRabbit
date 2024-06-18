#include "./coin.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <unordered_map>

struct CoinAnimationSpeedCoefs {
  static constexpr double Idle = 25;
  static constexpr double Shine = 25;
};

Coin::Coin(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
           Coordinates &currentCoords, const uint8_t &entityId,
           SnapshotWrapper &snapshot)
    : entityId(entityId), graphicEngine(graphicEngine),
      audioEngine(audioEngine), currentAnimation(nullptr),
      currentCoords(currentCoords), entityInfo(), shouldBeDeleted(false),
      isShowingExitAnimation(false),
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

void Coin::render(int iterationNumber) {}

void Coin::render(int iterationNumber, Coordinates &coords) {
  this->currentAnimation->render(iterationNumber, coords);
}

void Coin::update(bool isWalking, bool isRunning, std::string movingDirection) {
}

void Coin::updateByCoordsDelta(int deltaX, int deltaY) {
  this->currentCoords.setX(this->currentCoords.getX() + deltaX);
  this->currentCoords.setY(this->currentCoords.getY() + deltaY);
}

void Coin::renderFromLeftCorner(int iterationNumber,
                                const Coordinates &leftCorner) {
  this->currentAnimation->renderFromLeftCorner(iterationNumber, leftCorner,
                                               this->currentCoords);
}

void Coin::updateAnimation(const SnapshotWrapper &snapshot,
                           const CollectableDto &newEntityInfo) {}

void Coin::update(SnapshotWrapper &snapshot) {
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
    this->audioEngine.playCoinCollectedSound();
    return;
  }

  this->currentCoords.setX(newEntityInfo.position_x);
  this->currentCoords.setY(newEntityInfo.position_y);

  this->updateAnimation(snapshot, newEntityInfo);
  this->entityInfo = newEntityInfo;
}

uint8_t Coin::getId() const { return this->entityId; }

bool Coin::shouldDelete() const { return this->shouldBeDeleted; }

Coin::~Coin() {}
