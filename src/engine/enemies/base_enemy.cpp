
#include "base_enemy.h"

BaseEnemy::BaseEnemy(uint32_t id, Snapshot &snapshot, int pos)
    : id(id), health(100),
      rectangle(Rectangle(Coordinates(500, 1050), Coordinates(540, 1100))),
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
}
