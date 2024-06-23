#include "schwarzenguard.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint8_t DAMAGE = globalConfigs.getSchwarzenguardDamage();
const static uint8_t MAX_LIFE = globalConfigs.getSchwarzenguardMaxLife();
const static uint32_t POINTS = globalConfigs.getSchwarzenguardPoints();
const static double RESPAWN_TIME = globalConfigs.getSchwarzenguardRespawnTime();
const static float AMMO_DROP_CHANCE =
    globalConfigs.getSchwarzenguardAmmoDropChance();
const static float HEALTH_DROP_CHANCE =
    globalConfigs.getSchwarzenguardHealthDropChance();

Schwarzenguard::Schwarzenguard(uint32_t id, Snapshot &snapshot,
                               Rectangle rectangle)
    : BaseEnemy(id, snapshot, rectangle, MAX_LIFE, DAMAGE, POINTS, RESPAWN_TIME,
                AMMO_DROP_CHANCE, HEALTH_DROP_CHANCE) {}