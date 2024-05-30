#include "./jazz.h"
#include <yaml-cpp/yaml.h>

const static int COLOR_KEY_RGB[3] = {44, 102, 150};

Jazz::Jazz(SDL2pp::Renderer &sdlRenderer)
    : currentFrame(0), currentCoords(100, 100), sdlRenderer(sdlRenderer),
      surface("src/client/sprites/jazz/death/spritesheet.png"),
      colorKey(SDL_MapRGB(this->surface.Get()->format, COLOR_KEY_RGB[0],
                          COLOR_KEY_RGB[1], COLOR_KEY_RGB[2])),
      texture(this->sdlRenderer,
              this->surface.SetColorKey(true, this->colorKey)) {
  YAML::Node metadata =
      YAML::LoadFile("src/client/sprites/jazz/death/metadata.yaml");
  const YAML::Node &frames = metadata["frames"];
  this->maxAnimationFrames = frames.size();

  for (int i = 0; i < this->maxAnimationFrames; i++) {
    int x = frames[i]["frame"]["x"].as<int>();
    int y = frames[i]["frame"]["y"].as<int>();
    this->spriteCoords.push_back(Coordinates(x, y));
    this->width.push_back(frames[i]["frame"]["w"].as<int>());
    this->height.push_back(frames[i]["frame"]["h"].as<int>());
  }

  // Enable alpha blending for the sprites
  this->texture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

void Jazz::render(int it) {
  this->currentFrame = it % this->maxAnimationFrames;

  // Pick sprite from running animantion sequence
  int spriteX = this->spriteCoords[this->currentFrame].getX();
  int spriteY = this->spriteCoords[this->currentFrame].getY();
  int spriteWidth = this->width[this->currentFrame];
  int spriteHeight = this->height[this->currentFrame];

  int positionX = this->currentCoords.getX();
  positionX += 5;

  if (positionX > this->sdlRenderer.GetOutputWidth())
    positionX = -50;

  this->currentCoords.setX(positionX);

  int positionY =
      this->sdlRenderer.GetOutputHeight() / 2; // this->currentCoords.getY();

  // Draw player sprite
  this->sdlRenderer.Copy(
      this->texture, SDL2pp::Rect(spriteX, spriteY, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY - spriteHeight, spriteWidth,
                   spriteHeight));
}

Jazz::~Jazz() {}
