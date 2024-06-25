
#include "carrot.h"
#include <cstdint>
#include <iostream>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint8_t CARROT_HEAL = (uint8_t)globalConfigs.getCarrotHeal();

Carrot::Carrot(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id)
    : BaseCollectable(rectangle, snapshot, entity_id) {}

void Carrot::collect(BasePlayer &player) {
  player.heal(CARROT_HEAL);
  snapshot.collectables[entity_id].was_collected = NumericBool::True;
  collected = true;
  remove_from_snapshot();
}
