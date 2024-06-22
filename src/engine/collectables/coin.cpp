#include "coin.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint32_t COIN_POINTS = globalConfigs.getPointsPerCoin();

Coin::Coin(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id)
    : BaseCollectable(rectangle, snapshot, entity_id) {}

void Coin::collect(BasePlayer &player) {
  player.add_points(COIN_POINTS);
  snapshot.collectables[entity_id].was_collected = NumericBool::True;
  collected = true;
  remove_from_snapshot();
}
