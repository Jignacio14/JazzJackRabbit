
#include "bullet.h"

Bullet::Bullet(Snapshot &snap, uint8_t type, uint8_t damage, uint8_t speed,
               Rectangle rectangle, uint8_t facing_direction, ServerMap map)
    : snapshot(snap), type(type), damage(damage), speed(speed),
      rectangle(rectangle), facing_direction(facing_direction), map(map),
      id(snapshot.sizeBullets) {

  BulletDto new_bullet;
  new_bullet.position_x = rectangle.getTopLeftCorner().getX();
  new_bullet.position_y = rectangle.getTopLeftCorner().getY();
  new_bullet.type = type;
  new_bullet.entity_id = 1;

  snapshot.bullets[id] = new_bullet;
  snapshot.sizeBullets++;
}

void Bullet::move() {

  Rectangle new_rectangle = rectangle;
  if (facing_direction == FacingDirectionsIds::Right)
    new_rectangle.move_right(speed);
  else if (facing_direction == FacingDirectionsIds::Left)
    new_rectangle.move_left(speed);

  if (map.available_position(new_rectangle)) {
    rectangle = new_rectangle;
    snapshot.bullets[id].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.bullets[id].position_y = rectangle.getTopLeftCorner().getY();
  } else {
    // Choca con una pared, deberia desaparecer de la snapshot
  }

  // Verificar si choca con un jugador o un enemigo e inflingirle daño
}
