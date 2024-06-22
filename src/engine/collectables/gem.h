#ifndef GEM_H
#define GEM_H

#include "base_collectable.h"

class Gem : public BaseCollectable {

public:
  Gem(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id);

  void collect(BasePlayer &base_player) override;
};

#endif // GEM_H