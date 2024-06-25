
#ifndef JAZZJACKRABBIT_INITIAL_WEAPON_H
#define JAZZJACKRABBIT_INITIAL_WEAPON_H

#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include "base_weapon.h"

class InitialWeapon : public BaseWeapon {

public:
  explicit InitialWeapon(Snapshot &snap, int pos, uint8_t player_id);
  Bullet shoot(Rectangle rectangle, uint8_t facing_direction,
               ServerMap map) override;
  bool can_shoot() override;
};

#endif // JAZZJACKRABBIT_INITIAL_WEAPON_H
