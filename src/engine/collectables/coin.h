#ifndef COIN_H
#define COIN_H

#include "base_collectable.h"

class Coin : public BaseCollectable {

public:
  Coin(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id);

  void collect(BasePlayer &base_player) override;
};

#endif // COIN_H