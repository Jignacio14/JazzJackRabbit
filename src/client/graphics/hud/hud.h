#ifndef HUD_H
#define HUD_H

#include "../../../common/coordinates.h"
#include "../../player.h"
#include "../../renderable.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include "../text.h"
#include <SDL2pp/SDL2pp.hh>
#include <vector>

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
  Sprite &lifeHeartSprite;

  Sprite &jazzHudIcon;
  Sprite &spazHudIcon;
  Sprite &loriHudIcon;

  Sprite &gun1HudIcon;
  Sprite &gun2HudIcon;

  Text timeLeftText;
  Text pointsText;
  Text characterSelectedText;
  Text usernameText;
  Text lifeText;
  Text gun1Text;
  Text gun1TextShadow;
  Text gun2Text;
  Text gun2TextShadow;
  Text leaderboardText;

  void renderBackgroundFrame();
  std::string convertSecondsToMinutesSeconds(const int &totalSeconds);
  void renderTimeLeft(const double &timeLeft);
  void renderUsername();
  Sprite &getHudIcon(const PlayerDto &playerinfo);
  void renderHudIcon(const PlayerDto &playerinfo);
  void renderPoints(const PlayerDto &playerinfo);
  void renderCharacterSelected(const PlayerDto &playerinfo);
  void renderLife(const PlayerDto &playerinfo);
  void renderGun1(const PlayerDto &playerinfo);
  void renderGun2(const PlayerDto &playerinfo);
  void updatePlayersList(std::vector<std::string> &vector,
                         SnapshotWrapper &snapshot);
  void renderLeaderBoard(SnapshotWrapper &snapshot);

public:
  explicit Hud(GraphicEngine &graphicEngine, Player &player);

  virtual void render(int iterationNumber) override;

  virtual void render(int iterationNumber, Coordinates &coords) override;

  void render(SnapshotWrapper &snapshot);

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;

  static int getHorizontalSize();

  virtual uint8_t getId() const override;

  ~Hud() override;
};

#endif // HUD_H