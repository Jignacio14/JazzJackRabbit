#ifndef SCHWARZENGUARD_H
#define SCHWARZENGUARD_H

#include "base_enemy.h"

class Schwarzenguard : public BaseEnemy {
public:
  Schwarzenguard(uint32_t id, Snapshot &snapshot, int pos);
};

#endif // SCHWARZENGUARD_H