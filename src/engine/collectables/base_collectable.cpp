#include "base_collectable.h"
#include <cstdint>

BaseCollectable::BaseCollectable(Rectangle rectangle, Snapshot &snapshot,
                                 uint32_t entity_id)
    : rectangle(rectangle), snapshot(snapshot), entity_id((entity_id)) {}
