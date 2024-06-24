
#include "base_enemy.h"
#include <cstdint>
#include <iostream>

const static double ENEMY_COOLDOWN = 1;
const static double NEVER_ATTACKED = -1;

BaseEnemy::BaseEnemy(uint32_t id, Snapshot &snapshot, Rectangle rectangle,
                     uint8_t health, uint8_t damage, uint32_t points,
                     double respawn_time, float ammo_drop_chance,
                     float health_drop_chance, uint8_t max_health)
    : id(id), rectangle(rectangle), facing_direction(FacingDirectionsIds::Left),
      is_dead(false), snapshot(snapshot), health(health), damage(damage),
      points(points), respawn_time(respawn_time),
      ammo_drop_chance(ammo_drop_chance),
      health_drop_chance(health_drop_chance), moment_of_death(0),
      max_health(max_health),
      damage_rectangle(Rectangle(
          Coordinates(rectangle.getTopLeftCorner().getX() - DAMAGE_RANGE,
                      rectangle.getTopLeftCorner().getY()),
          Coordinates(rectangle.getBottomRightCorner().getX() + DAMAGE_RANGE,
                      rectangle.getBottomRightCorner().getY()))),
      cooldown(ENEMY_COOLDOWN), last_attack(NEVER_ATTACKED), time_passed(0) {

  std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

uint8_t BaseEnemy::receive_damage(uint8_t damage) {
  int index = find_position();
  if (damage >= health) {
    health = 0;
    is_dead = true;
    snapshot.enemies[index].is_dead = NumericBool::True;
    moment_of_death = snapshot.timeLeft;
    return determine_drop();
  } else {
    health -= damage;
    snapshot.enemies[index].was_hurt = NumericBool::True;
    return EnemyDrop::NoDrop;
  }
  std::cout << "Enemy " << id << " received " << (int)damage
            << " damage. Health: " << (int)health << std::endl;
}

uint8_t BaseEnemy::determine_drop() {
  float random = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
  if (random < ammo_drop_chance / 100.0f) {
    return EnemyDrop::Ammo;
  } else if (random < (ammo_drop_chance + health_drop_chance) / 100.0f) {
    return EnemyDrop::Carrot;
  } else {
    return EnemyDrop::NoDrop;
  }
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
  snapshot.enemies[index].shot = NumericBool::False;
  try_revive();
  if (last_attack >= 0)
    time_passed = (last_attack - snapshot.timeLeft);
}

void BaseEnemy::try_revive() {
  double time_passed_dead = (moment_of_death - snapshot.timeLeft);
  if (time_passed_dead >= respawn_time && is_dead) {
    health = max_health;
    is_dead = false;
    snapshot.enemies[find_position()].is_dead = NumericBool::False;
  }
}

Rectangle BaseEnemy::drop_rectangle() {
  Coordinates top_left(
      rectangle.getTopLeftCorner().getX() - HitboxSizes::CollectableWidth - 1,
      rectangle.getBottomRightCorner().getY() - HitboxSizes::CollectableHeight);
  Coordinates bottom_right(rectangle.getTopLeftCorner().getX() - 1,
                           rectangle.getBottomRightCorner().getY());
  return Rectangle(top_left, bottom_right);
}

void BaseEnemy::attack(BasePlayer &player) {
  if (player.is_alive()) {
    player.receive_damage(damage);
    last_attack = snapshot.timeLeft;
    int index = find_position();
    snapshot.enemies[index].shot = NumericBool::True;
  }
}

Rectangle BaseEnemy::get_damage_rectangle() { return damage_rectangle; }

bool BaseEnemy::can_attack() {
  if (last_attack == NEVER_ATTACKED)
    return true;
  else
    return (time_passed > cooldown && is_alive());
}
