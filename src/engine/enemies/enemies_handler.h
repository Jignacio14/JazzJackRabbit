#ifndef ENEMIES_HANDLER_H
#define ENEMIES_HANDLER_H

#include "../global_counter.h"
#include "bubba.h"
#include "schwarzenguard.h"
#include "turtle_goon.h"
#include <memory>
#include <vector>

class EnemiesHandler {

private:
  // cppcheck-suppress unusedStructMember
  std::vector<std::unique_ptr<BaseEnemy>> &enemies;
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;

public:
  EnemiesHandler(std::vector<std::unique_ptr<BaseEnemy>> &enemies,
                 Snapshot &snapshot);
  void initialize();
  void update();
};

#endif // ENEMIES_HANDLER_H