
#include "base_enemy.h"

BaseEnemy::BaseEnemy(uint8_t id, Snapshot &snapshot, int pos)
    : id(id), health(100),
      rectangle(Rectangle(Coordinates(500, 1050), Coordinates(540, 1100))),
      facing_direction(FacingDirectionsIds::Left), is_dead(NumericBool::False),
      snapshot(snapshot), position(pos) {}

void BaseEnemy::receive_damage(uint8_t damage) {
  if (damage >= health) {
    health = 0;
    is_dead = NumericBool::True;
    if (position != -1) {
      snapshot.enemies[position].is_dead = NumericBool::True;
      // Sacarlo de la snapshot
    }
  } else {
    health -= damage;
    if (position != -1) {
      snapshot.enemies[position].was_hurt = NumericBool::True;
    }
  }
}
