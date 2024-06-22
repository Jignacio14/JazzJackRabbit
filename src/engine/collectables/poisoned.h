#ifndef POISONED_H
#define POISONED_H

#include "base_collectable.h"

class Poisoned : public BaseCollectable {

public:
  Poisoned(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id);

  void collect(BasePlayer &base_player) override;
};

#endif // POISONED_H