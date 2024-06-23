
#include "base_enemy.h"
#include <iostream>

BaseEnemy::BaseEnemy(uint32_t id, Snapshot &snapshot, Rectangle rectangle,
                     uint8_t health, uint8_t damage, uint32_t points,
                     double respawn_time, float ammo_drop_chance,
                     float health_drop_chance)
    : id(id), rectangle(rectangle), facing_direction(FacingDirectionsIds::Left),
      is_dead(NumericBool::False), snapshot(snapshot), health(100),
      damage(damage), points(points), respawn_time(respawn_time),
      ammo_drop_chance(ammo_drop_chance),
      health_drop_chance(health_drop_chance) {}

void BaseEnemy::receive_damage(uint8_t damage) {
  int index = find_position();
  if (damage >= health) {
    health = 0;
    is_dead = NumericBool::True;
    snapshot.enemies[index].is_dead = NumericBool::True;
  } else {
    health -= damage;
    snapshot.enemies[index].was_hurt = NumericBool::True;
  }
  std::cout << "Enemy " << id << " received " << (int)damage
            << " damage. Health: " << (int)health << std::endl;
}

bool BaseEnemy::intersects(Rectangle rectangle) {
  return this->rectangle.intersects(rectangle);
}

bool BaseEnemy::is_alive() { return health > 0; }

int BaseEnemy::find_position() {
  for (int i = 0; i < snapshot.sizeEnemies; ++i) {
    if (snapshot.enemies[i].entity_id == id) {
      return i;
    }
  }
  return -1;
}

void BaseEnemy::update() {
  int index = find_position();
  snapshot.enemies[index].was_hurt = NumericBool::False;
}
