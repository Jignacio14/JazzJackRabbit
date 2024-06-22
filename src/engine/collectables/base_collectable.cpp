#include "base_collectable.h"
#include <cstdint>

BaseCollectable::BaseCollectable(Rectangle rectangle, Snapshot &snapshot,
                                 uint32_t entity_id)
    : rectangle(rectangle), snapshot(snapshot), entity_id((entity_id)),
      collected(false) {}

Rectangle BaseCollectable::get_rectangle() const { return rectangle; }

bool BaseCollectable::get_collected() const { return collected; }

void BaseCollectable::remove_from_snapshot() {
  for (uint32_t i = entity_id;
       i < static_cast<uint32_t>(snapshot.sizeCollectables) - 1; i++) {
    snapshot.collectables[i] = snapshot.collectables[i + 1];
  }
  snapshot.sizeCollectables--;
}
