#include "./sprite.h"
#include <yaml-cpp/yaml.h>

Sprite::Sprite(SDL2pp::Renderer &sdlRenderer, SDL2pp::Texture texture,
               std::string &animationBasePath)
    : sdlRenderer(sdlRenderer), texture(std::move(texture)),
      animationBasePath(animationBasePath) {

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
    : sdlRenderer(other.sdlRenderer), texture(std::move(other.texture)) {
  this->animationBasePath = other.animationBasePath;
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
