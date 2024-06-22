#ifndef BASE_COLLECTABLE_H
#define BASE_COLLECTABLE_H

#include "../../common/global_configs.h"
#include "../../common/rectangle.h"
#include "../../data/convention.h"
#include "../../data/snapshot_dto.h"
#include "../base_player.h"
#include <cstdint>
#include <sys/types.h>

class BaseCollectable {

protected:
  Rectangle rectangle;
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;
  // cppcheck-suppress unusedStructMember
  uint32_t entity_id;
  // cppcheck-suppress unusedStructMember
  bool collected;

public:
  // Constructor
  BaseCollectable(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id);

  virtual void collect(BasePlayer &base_player) = 0;

  Rectangle get_rectangle() const;

  bool get_collected() const;

  void remove_from_snapshot();
};

#endif // BASE_COLLECTABLE_H
