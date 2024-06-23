
#include "ammo.h"

Ammo::Ammo(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id)
    : BaseCollectable(rectangle, snapshot, entity_id) {}

void Ammo::collect(BasePlayer &player) {
  player.add_ammo();
  snapshot.collectables[entity_id].was_collected = NumericBool::True;
  collected = true;
  remove_from_snapshot();
}