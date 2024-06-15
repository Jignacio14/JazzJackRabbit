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

void Rectangle::move_left() {
  this->topLeftCorner.setX(this->topLeftCorner.getX() - 1);
  this->bottomRightCorner.setX(this->bottomRightCorner.getX() - 1);
}

void Rectangle::move_right() {
  this->topLeftCorner.setX(this->topLeftCorner.getX() + 1);
  this->bottomRightCorner.setX(this->bottomRightCorner.getX() + 1);
}

void Rectangle::move_down() {
  this->topLeftCorner.setY(this->topLeftCorner.getY() + 2);
  this->bottomRightCorner.setY(this->bottomRightCorner.getY() + 2);
}

void Rectangle::move_up() {
  this->topLeftCorner.setY(this->topLeftCorner.getY() - 2);
  this->bottomRightCorner.setY(this->bottomRightCorner.getY() - 2);
}

bool Rectangle::intersects(Rectangle other) const {
  /*
return (this->topLeftCorner.getX() <= other.getBottomRightCorner().getX() &&
        this->bottomRightCorner.getX() >= other.getTopLeftCorner().getX()) &&
       (this->bottomRightCorner.getY() <= other.getTopLeftCorner().getY() &&
        this->topLeftCorner.getY() >= other.getBottomRightCorner().getY());  */
  return !(this->bottomRightCorner.getX() < other.getTopLeftCorner().getX() ||
           this->topLeftCorner.getX() > other.getBottomRightCorner().getX() ||
           this->bottomRightCorner.getY() < other.getTopLeftCorner().getY() ||
           this->topLeftCorner.getY() > other.getBottomRightCorner().getY());
}
