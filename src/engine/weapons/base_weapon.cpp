
#include "base_weapon.h"

BaseWeapon::BaseWeapon(Snapshot &snap, uint16_t ammo, uint8_t damage,
                       float cooldown, uint8_t ammo_speed, int position)
    : snapshot(snap), ammo(ammo), damage(damage), cooldown(cooldown),
      ammo_speed(ammo_speed), player_pos(position) {}
