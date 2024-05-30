#ifndef JAZZ_H
#define JAZZ_H

#include "../coordinates.h"
#include "../renderable.h"
#include <SDL2pp/SDL2pp.hh>
#include <optional>
#include <vector>

class Jazz : public Renderable {
private:
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> spriteCoords;
  // cppcheck-suppress unusedStructMember
  std::vector<int> width;
  // cppcheck-suppress unusedStructMember
  std::vector<int> height;
  // cppcheck-suppress unusedStructMember
  int maxAnimationFrames;
  // cppcheck-suppress unusedStructMember
  int currentFrame;

  Coordinates currentCoords;

  SDL2pp::Renderer &sdlRenderer;
  SDL2pp::Surface surface;
  // cppcheck-suppress unusedStructMember
  uint32_t colorKey;
  SDL2pp::Texture texture;

public:
  explicit Jazz(SDL2pp::Renderer &sdlRenderer);
  virtual void render(int it) override;
  ~Jazz() override;
};

#endif // JAZZ_H
