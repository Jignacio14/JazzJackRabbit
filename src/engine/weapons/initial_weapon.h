
#ifndef JAZZJACKRABBIT_INITIAL_WEAPON_H
#define JAZZJACKRABBIT_INITIAL_WEAPON_H

#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include "base_weapon.h"

class InitialWeapon : public BaseWeapon {

public:
  explicit InitialWeapon(Snapshot &snap);
  Bullet shoot(Rectangle rectangle, uint8_t facing_direction,
               ServerMap map) override;
};

#endif // JAZZJACKRABBIT_INITIAL_WEAPON_H
