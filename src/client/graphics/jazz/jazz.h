#ifndef JAZZ_H
#define JAZZ_H

#include "../../coordinates.h"
#include "../../renderable.h"
#include "../graphic_engine.h"
#include "../playable_character.h"
#include "../sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <optional>
#include <string>
#include <vector>

class Jazz : public PlayableCharacter {
private:
  GraphicEngine &graphicEngine;
  // cppcheck-suppress unusedStructMember
  Sprite *currentState;
  // std::unique_ptr<AnimationState> currentAnimation;

  // cppcheck-suppress unusedStructMember
  int currentFrame;
  Coordinates &currentCoords;
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

  void debugUpdateLocation(int iterationNumber);

public:
  Jazz(GraphicEngine &graphicEngine, Coordinates &currentCoords);
  virtual void render(int iterationNumber) override;
  virtual void render(int iterationNumber, Coordinates &coords) override;
  virtual void updateByCoordsDelta(int deltaX, int deltaY) override;
  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;
  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection) override;
  ~Jazz() override;
};

#endif // JAZZ_H
