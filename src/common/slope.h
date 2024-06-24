#ifndef SLOPE_H
#define SLOPE_H

#include "../data/convention.h"
#include "./coordinates.h"
#include <cstdint>
#include <string>

class Slope {
private:
  Coordinates topLeftCorner;
  // cppcheck-suppress unusedStructMember
  std::string facingDirection;
  // Coordinates bottomRightCorner;

public:
  Slope(const Coordinates &topLeftCorner, const std::string &facingDirection);

  Slope(const Slope &other);
  Slope &operator=(const Slope &other);

  Coordinates getTopLeftCorner() const;
  std::string getFacingDirection() const;
};

#endif // SLOPE_H