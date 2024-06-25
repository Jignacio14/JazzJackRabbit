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

void Rectangle::move_left(const uint8_t &speed) {
  this->topLeftCorner.setX(this->topLeftCorner.getX() - speed);
  this->bottomRightCorner.setX(this->bottomRightCorner.getX() - speed);
}

void Rectangle::move_right(const uint8_t &speed) {
  this->topLeftCorner.setX(this->topLeftCorner.getX() + speed);
  this->bottomRightCorner.setX(this->bottomRightCorner.getX() + speed);
}

void Rectangle::move_down() {
  this->topLeftCorner.setY(this->topLeftCorner.getY() + 2);
  this->bottomRightCorner.setY(this->bottomRightCorner.getY() + 2);
}

void Rectangle::move_up() {
  this->topLeftCorner.setY(this->topLeftCorner.getY() - 2);
  this->bottomRightCorner.setY(this->bottomRightCorner.getY() - 2);
}

void Rectangle::move_vertically(const int &delta) {
  this->topLeftCorner.setY(this->topLeftCorner.getY() + delta);
  this->bottomRightCorner.setY(this->bottomRightCorner.getY() + delta);
}

bool Rectangle::intersects(const Rectangle &other) const {

  if (this->bottomRightCorner.getX() <= other.getTopLeftCorner().getX() ||
      other.getBottomRightCorner().getX() <= this->topLeftCorner.getX() ||
      this->bottomRightCorner.getY() <= other.getTopLeftCorner().getY() ||
      other.getBottomRightCorner().getY() <= this->topLeftCorner.getY()) {
    return false;
  }

  return true;
}

bool Rectangle::intersects_with_direction(const Rectangle &other,
                                          uint8_t &direction) const {

  if (this->bottomRightCorner.getX() <= other.getTopLeftCorner().getX() ||
      other.getBottomRightCorner().getX() <= this->topLeftCorner.getX() ||
      this->bottomRightCorner.getY() <= other.getTopLeftCorner().getY() ||
      other.getBottomRightCorner().getY() <= this->topLeftCorner.getY()) {
    return false;
  }

  int centerXThis =
      (this->topLeftCorner.getX() + this->bottomRightCorner.getX()) / 2.0f;
  int centerXOther =
      (other.getTopLeftCorner().getX() + other.getBottomRightCorner().getX()) /
      2.0f;

  if (centerXOther > centerXThis) {
    direction = FacingDirectionsIds::Right;
  } else {
    direction = FacingDirectionsIds::Left;
  }

  return true;
}
