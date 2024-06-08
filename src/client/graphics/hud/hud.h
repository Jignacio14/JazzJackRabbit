#ifndef HUD_H
#define HUD_H

#include "../../coordinates.h"
#include "../../renderable.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include <SDL2pp/SDL2pp.hh>

class Hud : public Renderable {
private:
  GraphicEngine &graphicEngine;
  SDL2pp::Renderer &sdlRenderer;
  SDL2pp::Rect hudBaseRectangle;

public:
  explicit Hud(GraphicEngine &graphicEngine);

  virtual void render(int iterationNumber) override;

  virtual void render(int iterationNumber, Coordinates &coords) override;

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;

  static int getHorizontalSize();

  ~Hud() override;
};

#endif // HUD_H