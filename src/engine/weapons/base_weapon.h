
#ifndef JAZZJACKRABBIT_BASE_WEAPON_H
#define JAZZJACKRABBIT_BASE_WEAPON_H

#include "../../common/rectangle.h"
#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include "../bullets/bullet.h"
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#define NEVER_SHOT (double)-1

class BaseWeapon {

protected:
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;
  // cppcheck-suppress unusedStructMember
  uint16_t ammo;
  // cppcheck-suppress unusedStructMember
  const uint8_t damage;
  // cppcheck-suppress unusedStructMember
  const double cooldown;
  // cppcheck-suppress unusedStructMember
  const uint8_t ammo_speed;
  // cppcheck-suppress unusedStructMember
  int player_pos;
  // cppcheck-suppress unusedStructMember
  double last_time_shot;
  // cppcheck-suppress unusedStructMember
  double time_passed;
  // cppcheck-suppress unusedStructMember
  uint8_t player_id;

public:
  BaseWeapon(Snapshot &snap, uint16_t ammo, uint8_t damage, double cooldown,
             uint8_t ammo_speed, int position, uint8_t player_id);
  virtual Bullet shoot(Rectangle rectangle, uint8_t facing_direction,
                       ServerMap map) = 0;
  virtual bool can_shoot() = 0;

  void update();
};

#endif // JAZZJACKRABBIT_BASE_WEAPON_H
