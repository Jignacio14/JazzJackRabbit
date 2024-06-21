
#include "carrot.h"
#include <cstdint>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint16_t CARROT_HEAL = globalConfigs.getCarrotHeal();

Carrot::Carrot(Rectangle rectangle, Snapshot &snapshot, uint32_t entity_id)
    : BaseCollectable(rectangle, snapshot, entity_id) {}

void Carrot::collect(BasePlayer &player) { player.heal(CARROT_HEAL); }
