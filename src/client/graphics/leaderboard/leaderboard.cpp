#include "./leaderboard.h"
#include "../../../common/global_configs.h"
#include "../hud/hud.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int HUD_HORIZONTAL_SIZE = Hud::getHorizontalSize();
const static int MAP_SCREEN_SIZE_X =
    globalConfigs.getScreenSizeX() - HUD_HORIZONTAL_SIZE;
const static int MAP_SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

const static SDL2pp::Color BLACK_COLOR = SDL2pp::Color(0, 0, 0, 100);

Leaderboard::Leaderboard(SDL2pp::Renderer &sdlRenderer)
    : sdlRenderer(sdlRenderer) {}

void Leaderboard::display(const SnapshotWrapper &snapshot) {

  this->sdlRenderer.SetDrawColor(BLACK_COLOR);
  SDL2pp::Rect rectangle(50, 50, MAP_SCREEN_SIZE_X - 100,
                         MAP_SCREEN_SIZE_Y - 100);
  this->sdlRenderer.DrawRect(rectangle);
  this->sdlRenderer.FillRect(rectangle);
  this->sdlRenderer.SetDrawColor(BLACK_COLOR);
}
