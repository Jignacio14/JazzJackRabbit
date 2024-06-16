#ifndef HUD_H
#define HUD_H

#include "../../../common/coordinates.h"
#include "../../player.h"
#include "../../renderable.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include "../text.h"
#include <SDL2pp/SDL2pp.hh>

class Hud : public Renderable {
private:
  GraphicEngine &graphicEngine;
  SDL2pp::Renderer &sdlRenderer;
  Player &player;

  // cppcheck-suppress unusedStructMember
  Coordinates hudLeftCorner;
  // cppcheck-suppress unusedStructMember
  int hudWidth;
  // cppcheck-suppress unusedStructMember
  int hudHeight;

  Sprite &frameSprite;

  Sprite &jazzHudIcon;
  Sprite &spazHudIcon;
  Sprite &loriHudIcon;

  Text pointsText;
  Text characterSelectedText;
  Text usernameText;

  void renderBackgroundFrame();
  Sprite &getHudIcon(const PlayerDto &playerinfo);
  void renderHudIcon(const PlayerDto &playerinfo);
  void renderPoints(const PlayerDto &playerinfo);
  void renderCharacterSelected(const PlayerDto &playerinfo);
  void renderUsername(const PlayerDto &playerinfo);

public:
  explicit Hud(GraphicEngine &graphicEngine, Player &player);

  virtual void render(int iterationNumber) override;

  virtual void render(int iterationNumber, Coordinates &coords) override;

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;

  static int getHorizontalSize();

  virtual uint8_t getId() const override;

  ~Hud() override;
};

#endif // HUD_H