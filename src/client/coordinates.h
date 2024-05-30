#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinates {
private:
  // cppcheck-suppress unusedStructMember
  int x;
  // cppcheck-suppress unusedStructMember
  int y;

public:
  Coordinates(int x, int y);

  Coordinates(const Coordinates &other);
  Coordinates &operator=(const Coordinates &other);

  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
};

#endif // COORDINATE_H
