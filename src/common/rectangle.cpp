#include "./rectangle.h"

Rectangle::Rectangle(const Coordinates &topLeftCorner,
                     const Coordinates &bottomRightCorner)
    : topLeftCorner(topLeftCorner), bottomRightCorner(bottomRightCorner) {}

Rectangle::Rectangle(const Rectangle &other)
    : topLeftCorner(other.topLeftCorner),
      bottomRightCorner(other.bottomRightCorner) {}

Rectangle &Rectangle::operator=(const Rectangle &other) {
  if (this == &other) {
    return *this;
  }

  this->topLeftCorner = other.topLeftCorner;
  this->bottomRightCorner = other.bottomRightCorner;

  return *this;
}

Coordinates Rectangle::getTopLeftCorner() const { return this->topLeftCorner; }

Coordinates Rectangle::getBottomRightCorner() const {
  return this->bottomRightCorner;
}
