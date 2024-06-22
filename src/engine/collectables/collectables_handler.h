#ifndef COLLECTABLES_HANDLER_H
#define COLLECTABLES_HANDLER_H

#include "../server_map.h"
#include "base_collectable.h"
#include "carrot.h"
#include <memory>
#include <vector>

class CollectablesHandler {
private:
  // cppcheck-suppress unusedStructMember
  std::vector<std::unique_ptr<BaseCollectable>> &collectables;
  // ServerMap &map;
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;

  void initialize_carrots();
  // void initializeGems();

public:
  CollectablesHandler(
      std::vector<std::unique_ptr<BaseCollectable>> &collectables,
      Snapshot &snapshot);
  void initialize();
};

#endif // COLLECTABLES_HANDLER_H