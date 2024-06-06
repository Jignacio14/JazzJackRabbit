#ifndef JAZZ_H
#define JAZZ_H

#include "../../coordinates.h"
#include "../../renderable.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <optional>
#include <vector>

class Jazz : public Renderable {
private:
  GraphicEngine &graphicEngine;
  Sprite &currentState;

  // cppcheck-suppress unusedStructMember
  int currentFrame;
  Coordinates currentCoords;

public:
  explicit Jazz(GraphicEngine &graphicEngine);
  virtual void render(int iterationNumber) override;
  ~Jazz() override;
};

#endif // JAZZ_H
