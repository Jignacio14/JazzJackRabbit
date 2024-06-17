#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "../../renderable.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include "../text.h"
#include <SDL2pp/SDL2pp.hh>
#include <vector>

class Leaderboard {
private:
  SDL2pp::Renderer &sdlRenderer;

public:
  explicit Leaderboard(SDL2pp::Renderer &sdlRenderer);
  void display(const SnapshotWrapper &snapshot);
};

#endif // LEADERBOARD_H