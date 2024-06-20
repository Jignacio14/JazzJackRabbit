
#ifndef JAZZJACKRABBIT_ORB_H
#define JAZZJACKRABBIT_ORB_H

#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include "base_weapon.h"
#include <cstdint>

class Orb : public BaseWeapon {

public:
  explicit Orb(Snapshot &snap, uint16_t ammo, int pos);
  Bullet shoot(Rectangle rectangle, uint8_t facing_direction,
               ServerMap map) override;
};

#endif // JAZZJACKRABBIT_ORB_H
