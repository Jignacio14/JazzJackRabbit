#ifndef TURTLE_GOON_H
#define TURTLE_GOON_H

#include "base_enemy.h"

class TurtleGoon : public BaseEnemy {
public:
  TurtleGoon(uint32_t id, Snapshot &snapshot, int pos);
};

#endif // TURTLE_GOON_H