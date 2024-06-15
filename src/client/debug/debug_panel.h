#ifndef DEBUG_PANEL_H
#define DEBUG_PANEL_H

#include "../graphics/text.h"
#include <SDL2pp/SDL2pp.hh>
#include <string>

class DebugPanel {
private:
  // cppcheck-suppress unusedStructMember
  bool isActive;
  // cppcheck-suppress unusedStructMember
  int currentFps;
  // cppcheck-suppress unusedStructMember
  int auxFrameCount;
  // cppcheck-suppress unusedStructMember
  double lastTimestamp;

  SDL2pp::Renderer &sdlRenderer;
  Text fpsText;

  double now();
  void updateFpsCount(double currentTimestamp);
  void displayFps();

public:
  explicit DebugPanel(SDL2pp::Renderer &sdlRenderer);
  void activationToggle();
  void beginFpsCount(double firstTimestamp);
  void display();
  void update(double currentTimestamp);
};

#endif // DEBUG_PANEL_H
