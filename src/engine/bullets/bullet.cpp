
#include "bullet.h"
#include <iostream>

Bullet::Bullet(uint8_t type, uint8_t damage, uint8_t speed, Rectangle rectangle,
               uint8_t facing_direction, ServerMap map)
    : type(type), damage(damage), speed(speed), rectangle(rectangle),
      facing_direction(facing_direction), map(map), id(999), alive(true) {}

void Bullet::add_to_snapshot(Snapshot &snapshot) {
  id = snapshot.sizeBullets;
  BulletDto new_bullet;
  new_bullet.position_x = rectangle.getTopLeftCorner().getX();
  new_bullet.position_y = rectangle.getTopLeftCorner().getY();
  new_bullet.type = type;
  new_bullet.entity_id = id;

  snapshot.bullets[id] = new_bullet;
  snapshot.sizeBullets = snapshot.sizeBullets + 1;
}

void Bullet::move(Snapshot &snapshot) {

  Rectangle new_rectangle = rectangle;
  if (facing_direction == FacingDirectionsIds::Right)
    new_rectangle.move_right(speed);
  else if (facing_direction == FacingDirectionsIds::Left)
    new_rectangle.move_left(speed);
  if (!map.available_position(new_rectangle)) {
    kill(snapshot);
  }
  if (alive) {
    rectangle = new_rectangle;
    snapshot.bullets[id].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.bullets[id].position_y = rectangle.getTopLeftCorner().getY();
  }
}

void Bullet::kill(Snapshot &snapshot) {
  bool found = false;
  alive = false;
  for (uint16_t i = 0; i < snapshot.sizeBullets; i++) {
    if (snapshot.bullets[i].entity_id == this->id) {
      found = true;
    }
    if (found && i < static_cast<uint32_t>(snapshot.sizeBullets) - 1) {
      snapshot.bullets[i] = snapshot.bullets[i + 1];
    }
  }
  if (found)
    snapshot.sizeBullets--;
}

Rectangle Bullet::get_rectangle() { return rectangle; }

uint8_t Bullet::get_damage() { return damage; }

bool Bullet::is_alive() { return alive; }
