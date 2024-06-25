#include "base_player.h"
#include "../common/global_configs.h"
#include "states/intoxicated.h"
#include <cstdint>
#include <iostream>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int MAX_HEALTH = globalConfigs.getPlayerMaxLife();
const static double INTOXICATED_TIME = globalConfigs.getIntoxicatedTime();
const static uint8_t SPECIAL_ATTACK_DAMAGE =
    globalConfigs.getSpecialAttackDamage();

const static int INITIAL_X = 60;
const static int INITIAL_Y = 1050;
const static uint16_t ADD_AMMO = 5;

BasePlayer::BasePlayer(uint8_t player_id, const std::string &player_name,
                       Snapshot &snapshot, int position, ServerMap &map)
    : player_id(player_id), player_name(player_name), health(MAX_HEALTH),
      state(std::make_unique<Alive>()),
      rectangle(Rectangle(Coordinates(INITIAL_X, INITIAL_Y),
                          Coordinates(INITIAL_X + HitboxSizes::PlayerWidth,
                                      INITIAL_Y + HitboxSizes::PlayerHeight))),
      facing_direction(FacingDirectionsIds::Right), map(map),
      snapshot(snapshot), position(position), positions_to_jump(0),
      is_moving(false), is_running(false), moment_of_death(0),
      weapon(std::make_unique<InitialWeapon>(snapshot, position, player_id)),
      orb_ammo(globalConfigs.getBullet2MaxAmmo()), points(0),
      intoxicated_start(0), doing_special_attack(false),
      lori_special_attack(false), special_attack_damage(SPECIAL_ATTACK_DAMAGE) {
}

int BasePlayer::find_position() {
  for (int i = 0; i < snapshot.sizePlayers; ++i) {
    if (snapshot.players[i].user_id == player_id)
      return i;
  }
  std::string errorMessage = "Player " + player_name + " not found in snapshot";
  throw JJR2Error(errorMessage, __LINE__, __FILE__);
}

void BasePlayer::update() {

  position = find_position();

  this->update_special_attack();

  this->update_jump();

  this->update_movement();

  this->update_intoxication();

  weapon->update();

  if (health == 0)
    this->try_respawn();

  snapshot.players[position].shot = NumericBool::False;
  snapshot.players[position].was_hurt = NumericBool::False;
  orb_ammo = snapshot.players[position].ammo_gun_2;
}

void BasePlayer::update_intoxication() {
  double time_passed = (intoxicated_start - snapshot.timeLeft);
  if (time_passed >= INTOXICATED_TIME &&
      snapshot.players[position].is_dead == NumericBool::False) {
    change_state(std::make_unique<Alive>());
    snapshot.players[position].is_intoxicated = NumericBool::False;
  }
}

void BasePlayer::try_respawn() {
  double time_passed = (moment_of_death - snapshot.timeLeft);
  if (time_passed >= globalConfigs.getRespawnTime()) {
    health = MAX_HEALTH;
    change_state(std::make_unique<Alive>());
    rectangle = Rectangle(Coordinates(INITIAL_X, INITIAL_Y),
                          Coordinates(INITIAL_X + HitboxSizes::PlayerWidth,
                                      INITIAL_Y + HitboxSizes::PlayerHeight));

    snapshot.players[position].is_dead = NumericBool::False;
    snapshot.players[position].life = health;
    snapshot.players[position].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.players[position].position_y = rectangle.getTopLeftCorner().getY();
  }
}

void BasePlayer::update_jump() {
  if (positions_to_jump > 0) {
    bool is_jumping = move_up();
    if (!is_jumping) {
      positions_to_jump = 0;
      snapshot.players[position].is_jumping = NumericBool::False;
    } else {
      positions_to_jump--;
    }

  } else {
    if (!doing_special_attack) {
      bool is_falling = move_down();
      if (!is_falling)
        snapshot.players[position].is_falling = NumericBool::False;
    }
  }
}

void BasePlayer::update_movement() {
  if (is_moving && facing_direction == FacingDirectionsIds::Right) {
    if (is_running)
      move_right(RUNNING_SPEED);
    else
      move_right(WALKING_SPEED);
  } else if (is_moving && facing_direction == FacingDirectionsIds::Left) {
    if (is_running)
      move_left(RUNNING_SPEED);
    else
      move_left(WALKING_SPEED);
  } else if (!is_moving) {
    is_running = false;
    snapshot.players[position].is_running = NumericBool::False;
  }
}

bool BasePlayer::move_down() {

  Rectangle new_rectangle(rectangle);
  new_rectangle.move_down();

  if (map.available_position(new_rectangle)) {
    rectangle = new_rectangle;

    int increment = 0;
    if (!map.available_position_slope(new_rectangle, increment)) {
      if (increment < 0) {
        return false;
      }
    }

    snapshot.players[position].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.players[position].position_y = rectangle.getTopLeftCorner().getY();
    snapshot.players[position].is_falling = NumericBool::True;
    snapshot.players[position].is_jumping = NumericBool::False;

    return true;
  }
  return false;
}

bool BasePlayer::move_up() {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_up();
  if (map.available_position(new_rectangle)) {
    rectangle = new_rectangle;

    snapshot.players[position].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.players[position].position_y = rectangle.getTopLeftCorner().getY();
    snapshot.players[position].is_jumping = NumericBool::True;

    return true;
  }
  return false;
}

void BasePlayer::move_right(uint8_t speed) {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_right(speed);
  if (state->can_move() && map.available_position(new_rectangle)) {

    int increment = 0;
    if (!map.available_position_slope(new_rectangle, increment)) {
      new_rectangle.move_vertically(increment);
    }

    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Right;
    is_moving = true;

    snapshot.players[position].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.players[position].position_y = rectangle.getTopLeftCorner().getY();
    snapshot.players[position].facing_direction = FacingDirectionsIds::Right;
    snapshot.players[position].is_walking = NumericBool::True;
  }
}

void BasePlayer::move_left(uint8_t speed) {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_left(speed);
  if (state->can_move() && map.available_position(new_rectangle)) {

    int increment = 0;
    if (!map.available_position_slope(new_rectangle, increment)) {
      new_rectangle.move_vertically(increment);
    }

    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Left;
    is_moving = true;

    snapshot.players[position].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.players[position].position_y = rectangle.getTopLeftCorner().getY();
    snapshot.players[position].facing_direction = FacingDirectionsIds::Left;
    snapshot.players[position].is_walking = NumericBool::True;
  }
}

void BasePlayer::receive_damage(uint8_t damage) {
  if (damage >= health) {
    health = 0;
    change_state(std::make_unique<Dead>());
    moment_of_death = snapshot.timeLeft;
    snapshot.players[position].is_dead = NumericBool::True;

  } else {
    health -= damage;
    snapshot.players[position].was_hurt = NumericBool::True;
  }
  snapshot.players[position].life = health;
}

void BasePlayer::change_state(std::unique_ptr<BaseState> new_state) {
  state = std::move(new_state);
}

void BasePlayer::run() {
  if ((snapshot.players[position].is_jumping == NumericBool::True) ||
      (snapshot.players[position].is_falling == NumericBool::True)) {
    return;
  }

  if (is_moving) {
    is_running = true;
    snapshot.players[position].is_running = NumericBool::True;
  }
}

void BasePlayer::stop_running() {
  is_running = false;
  snapshot.players[position].is_running = NumericBool::False;
}

void BasePlayer::jump() {
  if (snapshot.players[position].is_jumping == NumericBool::True ||
      snapshot.players[position].is_falling == NumericBool::True) {
    return;
  }

  if (this->can_jump()) {
    positions_to_jump = MAX_JUMP;
    snapshot.players[position].is_jumping = NumericBool::True;
  }
}

void BasePlayer::stop_moving() {
  is_moving = false;
  snapshot.players[position].is_walking = NumericBool::False;
}

void BasePlayer::get_intoxicated() {
  change_state(std::make_unique<Intoxicated>());
  snapshot.players[position].is_intoxicated = NumericBool::True;
  intoxicated_start = snapshot.timeLeft;
}

void BasePlayer::heal(uint8_t health_gain) {
  uint8_t new_health = health + health_gain;
  if (new_health > MAX_HEALTH) {
    health = MAX_HEALTH;
  } else {
    health = new_health;
  }
  snapshot.players[position].life = (uint16_t)health;
}

Bullet BasePlayer::shoot() {

  Rectangle bullet_rectangle(Coordinates(0, 0), Coordinates(0, 0));
  if (facing_direction == FacingDirectionsIds::Right) {
    Coordinates top_left(rectangle.getBottomRightCorner().getX() + 1,
                         rectangle.getTopLeftCorner().getY());
    Coordinates bottom_right(
        rectangle.getBottomRightCorner().getX() + HitboxSizes::BulletWidth + 1,
        rectangle.getTopLeftCorner().getY() + HitboxSizes::BulletHeight);
    Rectangle bullet_rectangle_aux(top_left, bottom_right);
    bullet_rectangle = bullet_rectangle_aux;
  } else if (facing_direction == FacingDirectionsIds::Left) {
    Coordinates top_left(rectangle.getTopLeftCorner().getX() -
                             HitboxSizes::BulletWidth - 1,
                         rectangle.getTopLeftCorner().getY());
    Coordinates bottom_right(rectangle.getTopLeftCorner().getX() - 1,
                             rectangle.getTopLeftCorner().getY() +
                                 HitboxSizes::BulletHeight);
    Rectangle bullet_rectangle_aux(top_left, bottom_right);
    bullet_rectangle = bullet_rectangle_aux;
  }
  if (this->can_shoot()) {
    snapshot.players[position].shot = NumericBool::True;
    return weapon->shoot(bullet_rectangle, facing_direction, map);
  } else {
    return Bullet(GunsIds::Gun1, INVALID_DAMAGE, 0, bullet_rectangle,
                  facing_direction, map, player_id);
  }
}

bool BasePlayer::intersects(Rectangle rectangle) {
  return this->rectangle.intersects(rectangle);
}

bool BasePlayer::is_alive() { return health > 0; }

void BasePlayer::change_weapon(uint8_t weapon_id) {
  switch (weapon_id) {
  case GunsIds::Gun1:
    weapon = std::make_unique<InitialWeapon>(snapshot, position, player_id);
    snapshot.players[position].current_gun = GunsIds::Gun1;
    break;
  case GunsIds::Gun2:
    weapon = std::make_unique<Orb>(snapshot, orb_ammo, position, player_id);
    snapshot.players[position].current_gun = GunsIds::Gun2;
    break;
  }
}

void BasePlayer::add_points(uint32_t points) {
  this->points += points;
  snapshot.players[position].points = this->points;
}

void BasePlayer::add_ammo() {
  orb_ammo += ADD_AMMO;
  snapshot.players[position].ammo_gun_2 = orb_ammo;
}

Rectangle BasePlayer::get_rectangle() { return rectangle; }

bool BasePlayer::can_shoot() {
  return (state->can_shoot() && weapon->can_shoot() && !doing_special_attack);
}

bool BasePlayer::can_jump() {
  return (positions_to_jump == 0 && state->can_jump() && !doing_special_attack);
}

bool BasePlayer::can_move() {
  if (lori_special_attack && health > 0)
    return true;
  else
    return (state->can_move() && !doing_special_attack && health > 0);
}

bool BasePlayer::is_doing_special_attack() { return doing_special_attack; }

uint8_t BasePlayer::get_special_attack_damage() {
  return special_attack_damage;
}

BasePlayer::~BasePlayer() {}
