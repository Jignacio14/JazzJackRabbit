#ifndef DISCONNECTED_OVERLAY_H
#define DISCONNECTED_OVERLAY_H

#include "../../renderable.h"
#include "../../sound/audio_engine.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include "../text.h"
#include <SDL2pp/SDL2pp.hh>
#include <vector>

class DisconnectedOverlay {
private:
  SDL2pp::Renderer &sdlRenderer;
  AudioEngine &audioEngine;
  Sprite &disconnectionSprite;

  // cppcheck-suppress unusedStructMember
  bool didRenderOnce;

  Text gameOverText;
  Text reasonText;

  void renderBackground();
  void renderHeader();
  void renderReason();

public:
  DisconnectedOverlay(SDL2pp::Renderer &sdlRenderer, AudioEngine &audioEngine,
                      Sprite &backgroundSprite);

  void display();
};

#endif // DISCONNECTED_OVERLAY_H