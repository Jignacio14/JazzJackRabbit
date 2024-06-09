/*#ifndef JAZZ_IDLE_H
#define JAZZ_IDLE_H

#include "../../../renderable.h"
#include "../animation_state.h"

class JazzIdle : public AnimationState {
private:
  GraphicEngine &graphicEngine;
  SDL2pp::Renderer &sdlRenderer;
  // cppcheck-suppress unusedStructMember
  int currentFrame;
  // cppcheck-suppress unusedStructMember
  Sprite *sprite;

public:
  explicit JazzIdle(GraphicEngine &graphicEngine);

  virtual void render(int iterationNumber, Coordinates &coords) override;

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner,
                                    const Coordinates &currentCoords) override;
};

#endif // JAZZ_IDLE_H
*/