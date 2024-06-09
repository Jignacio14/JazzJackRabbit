#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "../common/rectangle.h"
#include <vector>

class ServerMap {
private:
  std::vector<Rectangle> rectangles;
  // cppcheck-suppress unusedStructMember
  int fullMapSizeX;
  // cppcheck-suppress unusedStructMember
  int fullMapSizeY;

public:
  ServerMap();
};

#endif // SERVER_MAP_H