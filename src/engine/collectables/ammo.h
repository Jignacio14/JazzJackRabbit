#ifndef AMMO_H
#define AMMO_H

#include "base_collectable.h"
#include <cstdint>

class Ammo : public BaseCollectable {

public:
  Ammo(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id);

  void collect(BasePlayer &base_player) override;
};

#endif // AMMO_H