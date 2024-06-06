#include "./hud.h"

#include "../../../common/global_configs.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

static const int HUD_HORIZONTAL_SIZE = 150; // In px
static const int WHITE_RGBA[4] = {255, 255, 255, 255};
static const int BLACK_RGBA[4] = {0, 0, 0, 255};

Hud::Hud(GraphicEngine &graphicEngine)
    : graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      hudBaseRectangle(SCREEN_SIZE_X - HUD_HORIZONTAL_SIZE, 0, SCREEN_SIZE_X,
                       SCREEN_SIZE_Y) {}

void Hud::render(int iterationNumber) {
  this->sdlRenderer.SetDrawColor(WHITE_RGBA[0], WHITE_RGBA[1], WHITE_RGBA[2],
                                 WHITE_RGBA[3]);
  this->sdlRenderer.DrawRect(hudBaseRectangle);
  this->sdlRenderer.FillRect(hudBaseRectangle);
  this->sdlRenderer.SetDrawColor(BLACK_RGBA[0], BLACK_RGBA[1], BLACK_RGBA[2],
                                 BLACK_RGBA[3]);
}

int Hud::getHorizontalSize() { return HUD_HORIZONTAL_SIZE; }

Hud::~Hud() {}
