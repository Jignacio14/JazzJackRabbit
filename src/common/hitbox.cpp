#include "./hitbox.h"

Hitbox::Hitbox(int width, int height) : width(width), height(height) {}

Hitbox::Hitbox(const Hitbox &other)
    : width(other.width), height(other.height) {}

Hitbox &Hitbox::operator=(const Hitbox &other) {
  if (this == &other) {
    return *this;
  }

  this->width = other.width;
  this->height = other.height;

  return *this;
}

int Hitbox::getWidth() const { return this->width; }

int Hitbox::getHeight() const { return this->height; }

void Hitbox::setWidth(int width) { this->width = width; }

void Hitbox::setHeight(int height) { this->height = height; }
