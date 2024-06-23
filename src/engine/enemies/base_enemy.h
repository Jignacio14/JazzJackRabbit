
#ifndef JAZZJACKRABBIT_BASE_ENEMY_H
#define JAZZJACKRABBIT_BASE_ENEMY_H

#include "../../common/rectangle.h"
#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include <cstdint>
#include <memory>
#include <string>

class BaseEnemy {
protected:
  // cppcheck-suppress unusedStructMember
  uint32_t id;
  // cppcheck-suppress unusedStructMember
  uint8_t health;
  // cppcheck-suppress unusedStructMember
  Rectangle rectangle;
  // cppcheck-suppress unusedStructMember
  uint8_t facing_direction;
  // cppcheck-suppress unusedStructMember
  uint8_t is_dead;
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;

  int find_position();

public:
  BaseEnemy(uint32_t id, Snapshot &snapshot, Rectangle rectangle);
  void receive_damage(uint8_t damage);
  bool intersects(Rectangle rectangle);
  bool is_alive();
};

#endif // JAZZJACKRABBIT_BASE_ENEMY_H
