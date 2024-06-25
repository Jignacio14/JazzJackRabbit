#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "../common/rectangle.h"
#include "../common/slope.h"
#include <vector>

class ServerMap {
private:
  // cppcheck-suppress unusedStructMember
  std::vector<Rectangle> rectangles;
  // cppcheck-suppress unusedStructMember
  std::vector<Slope> slopes;
  // cppcheck-suppress unusedStructMember
  int fullMapSizeX;
  // cppcheck-suppress unusedStructMember
  int fullMapSizeY;

public:
  ServerMap();

  int getFullMapSizeX() const;

  bool available_position(Rectangle &rectangle) const;
  bool available_position_slope(Rectangle &rectangle, int &increment) const;
};

#endif // SERVER_MAP_H