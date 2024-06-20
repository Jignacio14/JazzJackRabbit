#ifndef CARROT_H
#define CARROT_H

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

class Carrot : public Renderable {
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
  Carrot(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
         Coordinates &currentCoords, const uint8_t &entityId,
         SnapshotWrapper &snapshot);

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;

  virtual void update(SnapshotWrapper &snapshot,
                      const Coordinates &leftCorner) override;

  virtual uint8_t getId() const override;

  virtual bool shouldDelete() const override;

  ~Carrot() override;
};

#endif // CARROT_H
