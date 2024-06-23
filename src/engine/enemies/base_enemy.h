
#ifndef JAZZJACKRABBIT_BASE_ENEMY_H
#define JAZZJACKRABBIT_BASE_ENEMY_H

#include "../../common/global_configs.h"
#include "../../common/rectangle.h"
#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include <cstdint>
#include <memory>
#include <string>

class BaseEnemy {
protected:
  // cppcheck-suppress unusedStructMember
  const uint32_t id;
  // cppcheck-suppress unusedStructMember
  Rectangle rectangle;
  // cppcheck-suppress unusedStructMember
  uint8_t facing_direction;
  // cppcheck-suppress unusedStructMember
  uint8_t is_dead;
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;
  // cppcheck-suppress unusedStructMember
  uint8_t health;
  // cppcheck-suppress unusedStructMember
  const uint8_t damage;
  // cppcheck-suppress unusedStructMember
  const uint32_t points;
  // cppcheck-suppress unusedStructMember
  const double respawn_time;
  // cppcheck-suppress unusedStructMember
  const float ammo_drop_chance;
  // cppcheck-suppress unusedStructMember
  const float health_drop_chance;
  // cppcheck-suppress unusedStructMember
  double moment_of_death;
  // cppcheck-suppress unusedStructMember
  const uint8_t max_health;

  int find_position();

public:
  BaseEnemy(uint32_t id, Snapshot &snapshot, Rectangle rectangle,
            uint8_t health, uint8_t damage, uint32_t points,
            double respawn_time, float ammo_drop_chance,
            float health_drop_chance, uint8_t max_health);
  void receive_damage(uint8_t damage);
  bool intersects(Rectangle rectangle);
  bool is_alive();
  void update();
  void try_revive();
};

#endif // JAZZJACKRABBIT_BASE_ENEMY_H
