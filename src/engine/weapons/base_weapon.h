
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

public:
  BaseWeapon(Snapshot &snap, uint16_t ammo, uint8_t damage, double cooldown,
             uint8_t ammo_speed, int position);
  virtual Bullet shoot(Rectangle rectangle, uint8_t facing_direction,
                       ServerMap map) = 0;
};

#endif // JAZZJACKRABBIT_BASE_WEAPON_H
