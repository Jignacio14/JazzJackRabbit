
#ifndef JAZZJACKRABBIT_BASE_ENEMY_H
#define JAZZJACKRABBIT_BASE_ENEMY_H

#include "../../common/rectangle.h"
#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include <cstdint>
#include <memory>
#include <string>

class BaseEnemy {
private:
  // cppcheck-suppress unusedStructMember
  uint16_t id;
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
  // cppcheck-suppress unusedStructMember
  int position;

public:
  BaseEnemy(uint8_t id, Snapshot &snapshot, int pos);
  void receive_damage(uint8_t damage);
};

#endif // JAZZJACKRABBIT_BASE_ENEMY_H
