#ifndef JAZZ_H
#define JAZZ_H

#include "../../coordinates.h"
#include "../../renderable.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <optional>
#include <string>
#include <vector>

class Jazz : public Renderable {
private:
  GraphicEngine &graphicEngine;
  Sprite &currentState;

  // cppcheck-suppress unusedStructMember
  int currentFrame;
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

  void debugUpdateLocation();

public:
  explicit Jazz(GraphicEngine &graphicEngine);
  virtual void render(int iterationNumber) override;
  virtual void updateByCoords(int x, int y) override;
  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection) override;
  ~Jazz() override;
};

#endif // JAZZ_H
