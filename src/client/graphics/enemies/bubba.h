#ifndef BUBBA_H
#define BUBBA_H

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

class Bubba : public Renderable {
private:
  // cppcheck-suppress unusedStructMember
  const uint8_t entityId;
  // cppcheck-suppress unusedStructMember
  const uint8_t type;
  GraphicEngine &graphicEngine;
  AudioEngine &audioEngine;

  std::unique_ptr<AnimationState> currentAnimation;

  Coordinates currentCoords;

  // cppcheck-suppress unusedStructMember
  EnemyDto entityInfo;
  Hitbox hitbox;

  void updateAnimation(const SnapshotWrapper &snapshot,
                       const EnemyDto &newEntityInfo);

public:
  Bubba(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
        Coordinates &currentCoords, const uint8_t &entityId,
        SnapshotWrapper &snapshot);

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;

  virtual void update(SnapshotWrapper &snapshot,
                      const Coordinates &leftCorner) override;

  virtual uint8_t getId() const override;

  virtual u_int8_t getType() const override;

  ~Bubba() override;
};

#endif // BUBBA_H
