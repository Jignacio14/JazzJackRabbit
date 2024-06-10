#ifndef AMMO_GUN_2_COLLECTABLE_H
#define AMMO_GUN_2_COLLECTABLE_H

#include "../../../common/coordinates.h"
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

class AmmoGun2 : public Renderable {
private:
  // cppcheck-suppress unusedStructMember
  const uint8_t entityId;
  GraphicEngine &graphicEngine;

  std::unique_ptr<AnimationState> currentAnimation;

  Coordinates currentCoords;

  // cppcheck-suppress unusedStructMember
  CollectableDto entityInfo;

  void updateAnimation(const SnapshotWrapper &snapshot,
                       const CollectableDto &newEntityInfo);

public:
  AmmoGun2(GraphicEngine &graphicEngine, Coordinates &currentCoords,
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

  ~AmmoGun2() override;
};

#endif // AMMO_GUN_2_COLLECTABLE_H
