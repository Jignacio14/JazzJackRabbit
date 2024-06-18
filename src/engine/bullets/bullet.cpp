
#include "bullet.h"
#include <iostream>

Bullet::Bullet(Snapshot &snap, uint8_t type, uint8_t damage, uint8_t speed,
               Rectangle rectangle, uint8_t facing_direction, ServerMap map)
    : snapshot(snap), type(type), damage(damage), speed(speed),
      rectangle(rectangle), facing_direction(facing_direction), map(map),
      id(snapshot.sizeBullets), alive(true) {

  BulletDto new_bullet;
  new_bullet.position_x = rectangle.getTopLeftCorner().getX();
  new_bullet.position_y = rectangle.getTopLeftCorner().getY();
  new_bullet.type = type;
  new_bullet.entity_id = id;

  snapshot.bullets[id] = new_bullet;
  snapshot.sizeBullets = snapshot.sizeBullets + 1;
}

void Bullet::move() {

  Rectangle new_rectangle = rectangle;
  if (facing_direction == FacingDirectionsIds::Right)
    new_rectangle.move_right(speed);
  else if (facing_direction == FacingDirectionsIds::Left)
    new_rectangle.move_left(speed);
  if (!map.available_position(new_rectangle)) {
    alive = false;
    delete_from_snapshot();
  }
  if (alive) {
    rectangle = new_rectangle;
    snapshot.bullets[id].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.bullets[id].position_y = rectangle.getTopLeftCorner().getY();
  }

  // Verificar si choca con un jugador o un enemigo e inflingirle daño
}

void Bullet::delete_from_snapshot() {
  for (uint16_t i = id; i < snapshot.sizeBullets - 1; i++) {
    snapshot.bullets[i] = snapshot.bullets[i + 1];
  }
  snapshot.sizeBullets--;
}

bool Bullet::is_alive() { return alive; }
