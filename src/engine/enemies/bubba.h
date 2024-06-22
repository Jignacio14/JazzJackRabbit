#ifndef BUBBA_H
#define BUBBA_H

#include "base_enemy.h"

class Bubba : public BaseEnemy {

public:
  Bubba(uint32_t id, Snapshot &snapshot, int pos);
};

#endif // BUBBA_H