#include "./debug_panel.h"
#include "../graphics/sprite_props.h"
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <cmath>

const static bool ACTIVE = true;
const static bool NOT_ACTIVE = false;

const static char EMPTY_FPS_TEXT[] = "FPS: 0";
const static int FONT_SIZE = 20;
const static SDL2pp::Color TEXT_COLOR = SDL2pp::Color(255, 255, 255, 255);

DebugPanel::DebugPanel(SDL2pp::Renderer &sdlRenderer)
    : isActive(NOT_ACTIVE), currentFps(0), auxFrameCount(0), lastTimestamp(0),
      sdlRenderer(sdlRenderer),
      fpsText(this->sdlRenderer, EMPTY_FPS_TEXT, TEXT_COLOR, FONT_SIZE,
              TextFontsCodes::Roboto) {}

double DebugPanel::now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(
             std::chrono::high_resolution_clock::now().time_since_epoch())
      .count();
}

void DebugPanel::displayFps() {
  std::string text = "FPS: " + std::to_string(this->currentFps);
  this->fpsText.updateInnerText(text);

  Coordinates coords(0, 0);
  this->fpsText.render(coords);
}

void DebugPanel::display() {
  if (!this->isActive) {
    return;
  }
  this->displayFps();
}

void DebugPanel::activationToggle() { this->isActive = !isActive; }

void DebugPanel::updateFpsCount(double currentTimestamp) {
  double elapsedTime = currentTimestamp - this->lastTimestamp;

  // If 1 second or more have passed
  if (elapsedTime >= 1.0) {
    this->currentFps = this->auxFrameCount;
    this->auxFrameCount = 0;
    this->lastTimestamp = currentTimestamp;
  }

  this->auxFrameCount++;
}

void DebugPanel::update(double currentTimestamp) {
  if (!this->isActive) {
    return;
  }

  this->updateFpsCount(currentTimestamp);
}
