
#ifndef JAZZJACKRABBIT_BASE_ENEMY_H
#define JAZZJACKRABBIT_BASE_ENEMY_H

#include "../../common/global_configs.h"
#include "../../common/rectangle.h"
#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include "../base_player.h"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <string>
#include <sys/types.h>

#define DAMAGE_RANGE 30

class BaseEnemy {
protected:
  // cppcheck-suppress unusedStructMember
  const uint32_t id;
  // cppcheck-suppress unusedStructMember
  Rectangle rectangle;
  // cppcheck-suppress unusedStructMember
  uint8_t facing_direction;
  // cppcheck-suppress unusedStructMember
  bool is_dead;
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
  // cppcheck-suppress unusedStructMember
  Rectangle damage_rectangle;
  // cppcheck-suppress unusedStructMember
  const double cooldown;
  // cppcheck-suppress unusedStructMember
  double last_attack;
  // cppcheck-suppress unusedStructMember
  double time_passed;

  int find_position();

  uint8_t determine_drop();

public:
  BaseEnemy(uint32_t id, Snapshot &snapshot, Rectangle rectangle,
            uint8_t health, uint8_t damage, uint32_t points,
            double respawn_time, float ammo_drop_chance,
            float health_drop_chance, uint8_t max_health);
  uint8_t receive_damage(uint8_t damage, bool &died);
  bool intersects(Rectangle rectangle);
  bool intersects_with_direction(Rectangle rectangle);
  bool is_alive();
  void update();
  void try_revive();
  Rectangle drop_rectangle();
  void attack(BasePlayer &player);
  bool can_attack();
  uint32_t get_points();
};

#endif // JAZZJACKRABBIT_BASE_ENEMY_H
