#ifndef SPAZ_H
#define SPAZ_H

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

class Spaz : public PlayableCharacter {
private:
  // cppcheck-suppress unusedStructMember
  const uint8_t entityId;
  GraphicEngine &graphicEngine;
  AudioEngine &audioEngine;

  std::unique_ptr<AnimationState> currentAnimation;

  Coordinates currentCoords;
  // cppcheck-suppress unusedStructMember
  bool isWalkingLeft;
  // cppcheck-suppress unusedStructMember
  bool isWalkingRight;
  // cppcheck-suppress unusedStructMember
  bool isWalkingUp;
  // cppcheck-suppress unusedStructMember
  bool isWalkingDown;
  // cppcheck-suppress unusedStructMember
  bool isRunning;
  // cppcheck-suppress unusedStructMember
  std::string movingDirection;

  // cppcheck-suppress unusedStructMember
  PlayerDto entityInfo;

  Hitbox hitbox;

  // void debugUpdateLocation(int iterationNumber);

  void updateAnimation(const SnapshotWrapper &snapshot,
                       const PlayerDto &newEntityInfo,
                       const Coordinates &leftCorner);

public:
  Spaz(GraphicEngine &graphicEngine, AudioEngine &audioEngine,
       Coordinates &currentCoords, const uint8_t &entityId,
       SnapshotWrapper &snapshot);

  virtual void render(int iterationNumber, Coordinates &coords) override;

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;

  virtual void update(SnapshotWrapper &snapshot,
                      const Coordinates &leftCorner) override;

  virtual uint8_t getId() const override;

  virtual Coordinates getCoords() override;
  virtual void setX(int x) override;
  virtual void setY(int y) override;

  ~Spaz() override;
};

#endif // SPAZ_H
