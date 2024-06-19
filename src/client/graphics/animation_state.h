#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include "../../common/hitbox.h"
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
  int totalRenders;
  // cppcheck-suppress unusedStructMember
  uint8_t spriteCode;
  // cppcheck-suppress unusedStructMember
  Sprite *sprite;
  // cppcheck-suppress unusedStructMember
  Hitbox &hitbox;

  bool shouldRenderLastFrame() const;

  void renderFrame(int positionX, int positionY);

  void renderLastFrameFromLeftCorner(const int &iterationNumber,
                                     const Coordinates &leftCorner,
                                     const Coordinates &currentCoords);

  void renderLastFrame(const int &iterationNumber, const Coordinates &coords);

public:
  explicit AnimationState(GraphicEngine &graphicEngine,
                          const uint8_t &spriteCode, Sprite *sprite,
                          const bool &shouldCycle,
                          const double &slowdownCoefficient,
                          const bool &shouldFlip, Hitbox &hitbox);

  // cppcheck-suppress unusedStructMember
  static constexpr bool Cycle = true;
  // cppcheck-suppress unusedStructMember
  static constexpr bool NotCycle = false;
  // cppcheck-suppress unusedStructMember
  static constexpr double DefaultSlowdown = 1.0;
  // cppcheck-suppress unusedStructMember
  static constexpr bool Flip = true;
  // cppcheck-suppress unusedStructMember
  static constexpr bool NotFlip = false;

  void render(int iterationNumber, const Coordinates &coords);

  void renderFromLeftCorner(int iterationNumber, const Coordinates &leftCorner,
                            const Coordinates &currentCoords);

  bool canBreakAnimation() const;

  uint8_t getCode() const;
};

#endif // ANIMATION_STATE_H
