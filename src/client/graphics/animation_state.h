#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include "../renderable.h"
#include "./graphic_engine.h"
#include <SDL2pp/SDL2pp.hh>

class AnimationState {
private:
  // cppcheck-suppress unusedStructMember
  const bool shouldCycle;
  // cppcheck-suppress unusedStructMember
  const bool shouldFlip;
  // cppcheck-suppress unusedStructMember
  double slowdownCoefficient;
  GraphicEngine &graphicEngine;
  SDL2pp::Renderer &sdlRenderer;
  // cppcheck-suppress unusedStructMember
  int currentFrame;
  // cppcheck-suppress unusedStructMember
  bool hasFinished;
  // cppcheck-suppress unusedStructMember
  uint32_t totalRenders;
  // cppcheck-suppress unusedStructMember
  uint8_t spriteCode;
  // cppcheck-suppress unusedStructMember
  Sprite *sprite;

  bool shouldRenderLastFrame() const;

  void renderFrame(int positionX, int positionY);

  void renderLastFrameFromLeftCorner(const int &iterationNumber,
                                     const Coordinates &leftCorner,
                                     const Coordinates &currentCoords);

  void renderLastFrame(const int &iterationNumber, const Coordinates &coords);

public:
  explicit AnimationState(GraphicEngine &graphicEngine,
                          const uint8_t &spriteCode, Sprite *sprite,
                          bool &shouldCycle, double &slowdownCoefficient,
                          bool &shouldFlip);

  // cppcheck-suppress unusedStructMember
  static const bool Cycle = true;
  // cppcheck-suppress unusedStructMember
  static const bool NotCycle = false;
  // cppcheck-suppress unusedStructMember
  static const double DefaultSlowdown = 1.0;
  // cppcheck-suppress unusedStructMember
  static const bool Flip = true;
  // cppcheck-suppress unusedStructMember
  static const bool NotFlip = false;

  void render(int iterationNumber, const Coordinates &coords);

  void renderFromLeftCorner(int iterationNumber, const Coordinates &leftCorner,
                            const Coordinates &currentCoords);

  bool canBreakAnimation() const;
};

#endif // ANIMATION_STATE_H
