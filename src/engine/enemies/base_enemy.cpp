
#include "base_enemy.h"
#include <iostream>

BaseEnemy::BaseEnemy(uint32_t id, Snapshot &snapshot, Rectangle rectangle)
    : id(id), health(100), rectangle(rectangle),
      facing_direction(FacingDirectionsIds::Left), is_dead(NumericBool::False),
      snapshot(snapshot) {}

void BaseEnemy::receive_damage(uint8_t damage) {
  if (damage >= health) {
    health = 0;
    is_dead = NumericBool::True;
    snapshot.enemies[id].is_dead = NumericBool::True;
  } else {
    health -= damage;
    snapshot.enemies[id].was_hurt = NumericBool::True;
  }
  std::cout << "Enemy " << id << " received " << (int)damage
            << " damage. Health: " << (int)health << std::endl;
}

bool BaseEnemy::intersects(Rectangle rectangle) {
  return this->rectangle.intersects(rectangle);
}

bool BaseEnemy::is_alive() { return health > 0; }
