#include "base_collectable.h"
#include <cstdint>

BaseCollectable::BaseCollectable(Rectangle rectangle, Snapshot &snapshot,
                                 uint32_t entity_id)
    : rectangle(rectangle), snapshot(snapshot), entity_id((entity_id)),
      collected(false) {}

Rectangle BaseCollectable::get_rectangle() const { return rectangle; }

bool BaseCollectable::get_collected() const { return collected; }

void BaseCollectable::remove_from_snapshot() {
  bool found = false;
  for (uint32_t i = 0; i < static_cast<uint32_t>(snapshot.sizeCollectables);
       i++) {
    if (snapshot.collectables[i].entity_id == this->entity_id) {
      found = true;
    }
    if (found && i < static_cast<uint32_t>(snapshot.sizeCollectables) - 1) {
      snapshot.collectables[i] = snapshot.collectables[i + 1];
    }
  }

  if (found) {
    snapshot.sizeCollectables--;
  }
}
