
#ifndef JAZZJACKRABBIT_BASE_BULLET_H
#define JAZZJACKRABBIT_BASE_BULLET_H

#include "../../common/rectangle.h"
#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include "../server_map.h"
#include <cstdint>

class Bullet {
private:
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;
  // cppcheck-suppress unusedStructMember
  uint8_t type;
  // cppcheck-suppress unusedStructMember
  uint8_t damage;
  // cppcheck-suppress unusedStructMember
  uint8_t speed;
  // cppcheck-suppress unusedStructMember
  Rectangle rectangle;
  // cppcheck-suppress unusedStructMember
  uint8_t facing_direction;
  // cppcheck-suppress unusedStructMember
  ServerMap map;
  // cppcheck-suppress unusedStructMember
  uint16_t id;

public:
  Bullet(Snapshot &snap, uint8_t type, uint8_t damage, uint8_t speed,
         Rectangle rectangle, uint8_t facing_direction, ServerMap map);
  void move();
};

#endif // JAZZJACKRABBIT_BASE_BULLET_H
