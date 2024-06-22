#include "gem.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint32_t GEM_POINTS = globalConfigs.getPointsPerGem();

Gem::Gem(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id)
    : BaseCollectable(rectangle, snapshot, entity_id) {}

void Gem::collect(BasePlayer &player) {
  player.add_points(GEM_POINTS);
  snapshot.collectables[entity_id].was_collected = NumericBool::True;
  collected = true;
  remove_from_snapshot();
}
