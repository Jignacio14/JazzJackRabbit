#include "bubba.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint8_t DAMAGE = globalConfigs.getBubbaDamage();
const static uint8_t MAX_LIFE = globalConfigs.getBubbaMaxLife();
const static uint32_t POINTS = globalConfigs.getBubbaPoints();
const static double RESPAWN_TIME = globalConfigs.getBubbaRespawnTime();
const static float AMMO_DROP_CHANCE = globalConfigs.getBubbaAmmoDropChance();
const static float HEALTH_DROP_CHANCE =
    globalConfigs.getBubbaHealthDropChance();

Bubba::Bubba(uint32_t id, Snapshot &snapshot, Rectangle rectangle)
    : BaseEnemy(id, snapshot, rectangle, MAX_LIFE, DAMAGE, POINTS, RESPAWN_TIME,
                AMMO_DROP_CHANCE, HEALTH_DROP_CHANCE) {}
