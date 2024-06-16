#ifndef BUBBA_H
#define BUBBA_H

#include "../../../common/coordinates.h"
#include "../../../common/hitbox.h"
#include "../../renderable.h"
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
  GraphicEngine &graphicEngine;

  std::unique_ptr<AnimationState> currentAnimation;

  Coordinates currentCoords;

  // cppcheck-suppress unusedStructMember
  EnemyDto entityInfo;
  Hitbox hitbox;

  void updateAnimation(const SnapshotWrapper &snapshot,
                       const EnemyDto &newEntityInfo);

public:
  Bubba(GraphicEngine &graphicEngine, Coordinates &currentCoords,
        const uint8_t &entityId, SnapshotWrapper &snapshot);

  virtual void render(int iterationNumber) override;
  virtual void render(int iterationNumber, Coordinates &coords) override;
  virtual void updateByCoordsDelta(int deltaX, int deltaY) override;
  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;
  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection) override;

  virtual void update(SnapshotWrapper &snapshot) override;

  virtual uint8_t getId() const override;

  ~Bubba() override;
};

#endif // BUBBA_H
