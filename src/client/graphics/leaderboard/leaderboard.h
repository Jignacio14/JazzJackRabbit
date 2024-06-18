#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "../../renderable.h"
#include "../../sound/audio_engine.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include "../text.h"
#include <SDL2pp/SDL2pp.hh>
#include <vector>

class Leaderboard {
private:
  SDL2pp::Renderer &sdlRenderer;
  AudioEngine &audioEngine;
  Sprite &backgroundSprite;

  // cppcheck-suppress unusedStructMember
  bool didRenderOnce;

  Text gameOverText;
  Text leaderboardTitleText;
  Text playersListText;

  void renderBackground();
  void renderHeader();
  void updatePlayersList(std::vector<std::string> &playersList,
                         SnapshotWrapper &snapshotWrapper);
  void renderPlayersList(SnapshotWrapper &snapshot);

public:
  Leaderboard(SDL2pp::Renderer &sdlRenderer, AudioEngine &audioEngine,
              Sprite &backgroundSprite);

  void display(SnapshotWrapper &snapshot);
};

#endif // LEADERBOARD_H