#ifndef CARROT_H
#define CARROT_H

#include "base_collectable.h"
#include <cstdint>

class Carrot : public BaseCollectable {

public:
  Carrot(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id);

  void collect(BasePlayer &base_player) override;
};

#endif // CARROT_H