#ifndef COLLECTABLES_HANDLER_H
#define COLLECTABLES_HANDLER_H

#include "ammo.h"
#include "base_collectable.h"
#include "carrot.h"
#include "coin.h"
#include "gem.h"
#include "poisoned.h"
#include <memory>
#include <vector>

class CollectablesHandler {
private:
  // cppcheck-suppress unusedStructMember
  std::vector<std::unique_ptr<BaseCollectable>> &collectables;
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;

  void initialize_carrots();
  void initialize_gems();
  void initialize_coins();

public:
  CollectablesHandler(
      std::vector<std::unique_ptr<BaseCollectable>> &collectables,
      Snapshot &snapshot);
  void initialize();
  void reset_collectables();
  void add_ammo(Rectangle rectangle);
  void add_carrot(Rectangle rectangle);
};

#endif // COLLECTABLES_HANDLER_H