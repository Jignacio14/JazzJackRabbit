#include "./slope.h"

Slope::Slope(const Coordinates &topLeftCorner,
             const std::string &facingDirection)
    : topLeftCorner(topLeftCorner), facingDirection(facingDirection) {}

Slope::Slope(const Slope &other)
    : topLeftCorner(other.topLeftCorner),
      facingDirection(other.facingDirection) {}

Slope &Slope::operator=(const Slope &other) {
  if (this == &other) {
    return *this;
  }

  this->topLeftCorner = other.topLeftCorner;
  this->facingDirection = other.facingDirection;

  return *this;
}

Coordinates Slope::getTopLeftCorner() const { return this->topLeftCorner; }

std::string Slope::getFacingDirection() const { return this->facingDirection; }

/*Slope::Slope(const Coordinates &topLeftCorner,
                     const Coordinates &bottomRightCorner)
    : topLeftCorner(topLeftCorner), bottomRightCorner(bottomRightCorner) {}

Slope::Slope(const Slope &other)
    : topLeftCorner(other.topLeftCorner),
      bottomRightCorner(other.bottomRightCorner) {}

Slope &Slope::operator=(const Slope &other) {
  if (this == &other) {
    return *this;
  }

  this->topLeftCorner = other.topLeftCorner;
  this->bottomRightCorner = other.bottomRightCorner;

  return *this;
}

Coordinates Slope::getTopLeftCorner() const { return this->topLeftCorner; }

Coordinates Slope::getBottomRightCorner() const {
  return this->bottomRightCorner;
}

void Slope::move_left(uint8_t speed) {
  this->topLeftCorner.setX(this->topLeftCorner.getX() - speed);
  this->bottomRightCorner.setX(this->bottomRightCorner.getX() - speed);
}

void Slope::move_right(uint8_t speed) {
  this->topLeftCorner.setX(this->topLeftCorner.getX() + speed);
  this->bottomRightCorner.setX(this->bottomRightCorner.getX() + speed);
}

void Slope::move_down() {
  this->topLeftCorner.setY(this->topLeftCorner.getY() + 2);
  this->bottomRightCorner.setY(this->bottomRightCorner.getY() + 2);
}

void Slope::move_up() {
  this->topLeftCorner.setY(this->topLeftCorner.getY() - 2);
  this->bottomRightCorner.setY(this->bottomRightCorner.getY() - 2);
}

bool Slope::intersects(Slope other) const {

  if (this->bottomRightCorner.getX() <= other.getTopLeftCorner().getX() ||
      other.getBottomRightCorner().getX() <= this->topLeftCorner.getX() ||
      this->bottomRightCorner.getY() <= other.getTopLeftCorner().getY() ||
      other.getBottomRightCorner().getY() <= this->topLeftCorner.getY()) {
    return false;
  }

  return true;
}

bool Slope::intersects_with_direction(Slope other,
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
}*/
