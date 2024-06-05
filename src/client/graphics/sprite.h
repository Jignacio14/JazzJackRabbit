#ifndef SPRITE_H
#define SPRITE_H

#include "../coordinates.h"
#include "../renderable.h"
#include <SDL2pp/SDL2pp.hh>
#include <vector>

class Sprite : public Renderable {
private:
  SDL2pp::Renderer &sdlRenderer;
  SDL2pp::Texture texture;

  // cppcheck-suppress unusedStructMember
  std::string animationBasePath;
  // cppcheck-suppress unusedStructMember
  int currentFrame;
  Coordinates currentCoords;

  // cppcheck-suppress unusedStructMember
  int maxAnimationFrames;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> spriteCoords;
  // cppcheck-suppress unusedStructMember
  std::vector<int> width;
  // cppcheck-suppress unusedStructMember
  std::vector<int> height;

public:
  Sprite(SDL2pp::Renderer &sdlRenderer, SDL2pp::Texture texture,
         std::string &animationBasePath);

  /*
   * Sprite cannot be copied
   */
  Sprite(const Sprite &) = delete;
  Sprite &operator=(const Sprite &) = delete;

  /*
   * Sprite can be moved
   */
  Sprite(Sprite &&);
  Sprite &operator=(Sprite &&);

  virtual void render(int iterationNumber) override;

  ~Sprite() override;
};

#endif // SPRITE_H
