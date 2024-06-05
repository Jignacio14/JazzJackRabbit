#include "./sprite.h"
#include <yaml-cpp/yaml.h>

Sprite::Sprite(SDL2pp::Renderer &sdlRenderer, SDL2pp::Texture texture,
               std::string &animationBasePath)
    : sdlRenderer(sdlRenderer), texture(std::move(texture)),
      animationBasePath(animationBasePath), currentFrame(0),
      currentCoords(100, 100) {

  YAML::Node metadata =
      YAML::LoadFile(this->animationBasePath + "/metadata.yaml");

  const YAML::Node &frames = metadata["frames"];
  this->maxAnimationFrames = frames.size();

  for (int i = 0; i < this->maxAnimationFrames; i++) {
    int x = frames[i]["frame"]["x"].as<int>();
    int y = frames[i]["frame"]["y"].as<int>();
    this->spriteCoords.push_back(Coordinates(x, y));
    this->width.push_back(frames[i]["frame"]["w"].as<int>());
    this->height.push_back(frames[i]["frame"]["h"].as<int>());
  }
}

Sprite::Sprite(Sprite &&other)
    : sdlRenderer(other.sdlRenderer), texture(std::move(other.texture)),
      currentCoords(other.currentCoords) {
  this->animationBasePath = other.animationBasePath;
  this->currentFrame = other.currentFrame;
  this->maxAnimationFrames = other.maxAnimationFrames;

  for (auto &item : other.spriteCoords) {
    this->spriteCoords.push_back(item);
  }

  for (auto &item : other.width) {
    this->width.push_back(item);
  }

  for (auto &item : other.height) {
    this->height.push_back(item);
  }
}

Sprite &Sprite::operator=(Sprite &&other) {
  if (this == &other)
    return *this;

  this->sdlRenderer = std::move(other.sdlRenderer);
  this->texture = std::move(other.texture);
  this->animationBasePath = other.animationBasePath;
  this->currentFrame = other.currentFrame;
  this->currentCoords = other.currentCoords;
  this->maxAnimationFrames = other.maxAnimationFrames;

  for (auto &item : other.spriteCoords) {
    this->spriteCoords.push_back(item);
  }

  for (auto &item : other.width) {
    this->width.push_back(item);
  }

  for (auto &item : other.height) {
    this->height.push_back(item);
  }

  return *this;
}

void Sprite::render(int iterationNumber) {
  this->currentFrame = iterationNumber % this->maxAnimationFrames;

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

Sprite::~Sprite() {}
