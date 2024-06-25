#include "./slope.h"

const static int TILE_SIZE = 32;
const static int HEIGHT_PADDING_TO_AVOID_COLLISION_WITH_SQUARE_CORNERS =
    4; // In px

Slope::Slope(const Coordinates &topLeftCorner,
             const std::string &facingDirection)
    : topLeftCorner(topLeftCorner),
      bottomRightCorner(Coordinates(this->topLeftCorner.getX() + TILE_SIZE,
                                    this->topLeftCorner.getY() + TILE_SIZE)),
      facingDirection(facingDirection) {}

Slope::Slope(const Slope &other)
    : topLeftCorner(other.topLeftCorner),
      bottomRightCorner(other.bottomRightCorner),
      facingDirection(other.facingDirection) {}

Slope &Slope::operator=(const Slope &other) {
  if (this == &other) {
    return *this;
  }

  this->topLeftCorner = other.topLeftCorner;
  this->bottomRightCorner = other.bottomRightCorner;
  this->facingDirection = other.facingDirection;

  return *this;
}

Coordinates Slope::getTopLeftCorner() const { return this->topLeftCorner; }

std::string Slope::getFacingDirection() const { return this->facingDirection; }

int Slope::calculateIncrementForIntersection(const Rectangle &other) const {
  int increment = 0;

  if (this->facingDirection == "left") {
    int overlapX = std::abs(other.getBottomRightCorner().getX() -
                            this->topLeftCorner.getX());
    int desiredHeightFromSlopeBottom =
        overlapX; // Because the slopes are at 45°

    int overlapY = std::abs(other.getBottomRightCorner().getY() -
                            this->topLeftCorner.getY());
    int deltaY = TILE_SIZE - overlapY;

    increment = deltaY - desiredHeightFromSlopeBottom -
                HEIGHT_PADDING_TO_AVOID_COLLISION_WITH_SQUARE_CORNERS;

  } else {
    int overlapX = std::abs(this->bottomRightCorner.getX() -
                            other.getTopLeftCorner().getX());
    int desiredHeightFromSlopeBottom =
        overlapX; // Because the slopes are at 45°

    int overlapY = std::abs(other.getBottomRightCorner().getY() -
                            this->topLeftCorner.getY());
    int deltaY = TILE_SIZE - overlapY;

    increment = deltaY - desiredHeightFromSlopeBottom -
                HEIGHT_PADDING_TO_AVOID_COLLISION_WITH_SQUARE_CORNERS;
  }

  return increment;
}

bool Slope::intersects(const Rectangle &other, int &increment) const {
  bool doesRectangleIntersects = true;
  if (this->bottomRightCorner.getX() <= other.getTopLeftCorner().getX() ||
      other.getBottomRightCorner().getX() <= this->topLeftCorner.getX() ||
      this->bottomRightCorner.getY() <= other.getTopLeftCorner().getY() ||
      other.getBottomRightCorner().getY() <= this->topLeftCorner.getY()) {
    doesRectangleIntersects = false;
  }

  if (!doesRectangleIntersects) {
    return doesRectangleIntersects;
  }

  increment = this->calculateIncrementForIntersection(other);

  return doesRectangleIntersects;
}
