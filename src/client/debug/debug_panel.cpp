#include "./debug_panel.h"
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <cmath>

const static bool ACTIVE = true;
const static bool NOT_ACTIVE = false;

const static char FONT_PATH[] = "src/client/graphics/Roboto.ttf";
const static int FONT_SIZE = 20;
const static SDL_Color TEXT_COLOR = {255, 255, 255, 255};

DebugPanel::DebugPanel(SDL2pp::Renderer &sdlRenderer)
    : isActive(NOT_ACTIVE), currentFps(0), auxFrameCount(0), lastTimestamp(0),
      sdlRenderer(sdlRenderer), font(FONT_PATH, FONT_SIZE) {}

double DebugPanel::now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(
             std::chrono::high_resolution_clock::now().time_since_epoch())
      .count();
}

void DebugPanel::displayFps() {
  std::string text = "FPS: " + std::to_string(this->currentFps);
  SDL2pp::Texture textSprite(this->sdlRenderer,
                             this->font.RenderText_Blended(text, TEXT_COLOR));

  this->sdlRenderer.Copy(
      textSprite, SDL2pp::NullOpt,
      SDL2pp::Rect(0, 0, textSprite.GetWidth(), textSprite.GetHeight()));
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
