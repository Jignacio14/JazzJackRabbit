#ifndef SLOPE_H
#define SLOPE_H

#include "../data/convention.h"
#include "./coordinates.h"
#include "./rectangle.h"
#include <cstdint>
#include <string>

class Slope {
private:
  Coordinates topLeftCorner;
  Coordinates bottomRightCorner;
  // cppcheck-suppress unusedStructMember
  std::string facingDirection;

  int calculateIncrementForIntersection(const Rectangle &other) const;

public:
  Slope(const Coordinates &topLeftCorner, const std::string &facingDirection);

  Slope(const Slope &other);
  Slope &operator=(const Slope &other);

  Coordinates getTopLeftCorner() const;
  std::string getFacingDirection() const;

  bool intersects(const Rectangle &other, int &increment) const;
};

#endif // SLOPE_H