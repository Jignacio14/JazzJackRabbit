#include "./coordinates.h"

Coordinates::Coordinates(int x, int y) : x(x), y(y) {}

Coordinates::Coordinates(const Coordinates &other) : x(other.x), y(other.y) {}

Coordinates &Coordinates::operator=(const Coordinates &other) {
  if (this == &other) {
    return *this;
  }

  this->x = other.x;
  this->y = other.y;

  return *this;
}

int Coordinates::getX() const { return this->x; }

int Coordinates::getY() const { return this->y; }

void Coordinates::setX(int x) { this->x = x; }

void Coordinates::setY(int y) { this->y = y; }
