#include "poisoned.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static double INTOXICATED_TIME = globalConfigs.getIntoxicatedTime();

Poisoned::Poisoned(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id)
    : BaseCollectable(rectangle, snapshot, entity_id) {}

void Poisoned::collect(BasePlayer &player) {
  player.get_intoxicated();
  snapshot.collectables[entity_id].was_collected = NumericBool::True;
  collected = true;
  remove_from_snapshot();
}