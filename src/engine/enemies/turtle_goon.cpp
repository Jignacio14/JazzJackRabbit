#include "turtle_goon.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint8_t DAMAGE = globalConfigs.getTurtleDamage();
const static uint8_t MAX_LIFE = globalConfigs.getTurtleMaxLife();
const static uint32_t POINTS = globalConfigs.getTurtlePoints();
const static double RESPAWN_TIME = globalConfigs.getTurtleRespawnTime();
const static float AMMO_DROP_CHANCE = globalConfigs.getTurtleAmmoDropChance();
const static float HEALTH_DROP_CHANCE =
    globalConfigs.getTurtleHealthDropChance();

TurtleGoon::TurtleGoon(uint32_t id, Snapshot &snapshot, Rectangle rectangle)
    : BaseEnemy(id, snapshot, rectangle, MAX_LIFE, DAMAGE, POINTS, RESPAWN_TIME,
                AMMO_DROP_CHANCE, HEALTH_DROP_CHANCE, MAX_LIFE) {}
