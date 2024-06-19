#ifndef COIN_H
#define COIN_H

#include "../../../common/coordinates.h"
#include "../../../common/hitbox.h"
#include "../../renderable.h"
#include "../../sound/audio_engine.h"
#include "../graphic_engine.h"
#include "../playable_character.h"
#include "../sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "../animation_state.h"

class Coin : public Renderable {
private:
  // cppcheck-suppress unusedStructMember
  const uint8_t entityId;
  GraphicEngine &graphicEngine;
  AudioEngine &audioEngine;

  std::unique_ptr<AnimationState> currentAnimation;

  Coordinates currentCoords;

  // cppcheck-suppress unusedStructMember
  CollectableDto entityInfo;
  // cppcheck-suppress unusedStructMember
  bool shouldBeDeleted;
  // cppcheck-suppress unusedStructMember
  bool isShowingExitAnimation;
  Hitbox hitbox;

  void updateAnimation(const SnapshotWrapper &snapshot,
                       const CollectableDto &newEntityInfo);

public:
  Coin(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
       Coordinates &currentCoords, const uint8_t &entityId,
       SnapshotWrapper &snapshot);

  virtual void render(int iterationNumber) override;
  virtual void render(int iterationNumber, Coordinates &coords) override;
  virtual void updateByCoordsDelta(int deltaX, int deltaY) override;
  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;
  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection) override;

  virtual void update(SnapshotWrapper &snapshot) override;

  virtual uint8_t getId() const override;

  virtual bool shouldDelete() const override;

  ~Coin() override;
};

#endif // COIN_H
