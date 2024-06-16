#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "./coordinates.h"
#include <cstdint>

class Rectangle {
private:
  Coordinates topLeftCorner;
  Coordinates bottomRightCorner;

public:
  Rectangle(const Coordinates &topLeftCorner,
            const Coordinates &bottomRightCorner);

  Rectangle(const Rectangle &other);
  Rectangle &operator=(const Rectangle &other);

  Coordinates getTopLeftCorner() const;

  Coordinates getBottomRightCorner() const;

  void move_left(uint8_t speed);

  void move_right(uint8_t speed);

  void move_down();

  void move_up();

  bool intersects(Rectangle other) const;
};

#endif // RECTANGLE_H