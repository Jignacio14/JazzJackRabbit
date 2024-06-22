#include "base_player.h"

#include "../common/global_configs.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int MAX_HEALTH = globalConfigs.getPlayerMaxLife();

const static int INITIAL_X = 60;
const static int INITIAL_Y = 1050;

BasePlayer::BasePlayer(uint8_t player_id, const std::string &player_name,
                       Snapshot &snapshot, int position)
    : player_id(player_id), player_name(player_name), health(MAX_HEALTH),
      state(std::make_unique<Alive>()),
      rectangle(Rectangle(Coordinates(INITIAL_X, INITIAL_Y),
                          Coordinates(INITIAL_X + HitboxSizes::PlayerWidth,
                                      INITIAL_Y + HitboxSizes::PlayerHeight))),
      facing_direction(FacingDirectionsIds::Right), snapshot(snapshot),
      position(position), positions_to_jump(0), is_moving(false),
      is_running(false), moment_of_death(0),
      weapon(std::make_unique<InitialWeapon>(snapshot, position)),
      orb_ammo(globalConfigs.getBullet2MaxAmmo()) {}

int BasePlayer::find_position() {
  for (int i = 0; i < snapshot.sizePlayers; ++i) {
    if (snapshot.players[i].user_id == player_id)
      return i;
  }
  return -1;
}

void BasePlayer::update() {
  position = find_position();

  this->update_jump();

  this->update_movement();

  weapon->update();

  if (health == 0)
    this->try_respawn();

  if (position != -1) {
    snapshot.players[position].shot = NumericBool::False;
    snapshot.players[position].was_hurt = NumericBool::False;
    orb_ammo = snapshot.players[position].ammo_gun_2;
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

    if (position != -1) {
      snapshot.players[position].is_dead = NumericBool::False;
      snapshot.players[position].life = health;
      snapshot.players[position].position_x =
          rectangle.getTopLeftCorner().getX();
      snapshot.players[position].position_y =
          rectangle.getTopLeftCorner().getY();
    }
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
    bool is_falling = move_down();
    if (!is_falling)
      snapshot.players[position].is_falling = NumericBool::False;
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

    if (position != -1) {
      snapshot.players[position].position_x =
          rectangle.getTopLeftCorner().getX();
      snapshot.players[position].position_y =
          rectangle.getTopLeftCorner().getY();
      snapshot.players[position].is_falling = NumericBool::True;
      snapshot.players[position].is_jumping = NumericBool::False;
    }
    return true;
  }
  return false;
}

bool BasePlayer::move_up() {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_up();
  if (map.available_position(new_rectangle)) {
    rectangle = new_rectangle;

    if (position != -1) {
      snapshot.players[position].position_x =
          rectangle.getTopLeftCorner().getX();
      snapshot.players[position].position_y =
          rectangle.getTopLeftCorner().getY();
      snapshot.players[position].is_jumping = NumericBool::True;
    }
    return true;
  }
  return false;
}

void BasePlayer::receive_damage(uint8_t damage) {
  if (damage >= health) {
    health = 0;
    change_state(std::make_unique<Dead>());
    moment_of_death = snapshot.timeLeft;
    if (position != -1) {
      snapshot.players[position].is_dead = NumericBool::True;
      snapshot.players[position].life = health;
    }
  } else {
    health -= damage;
    if (position != -1) {
      snapshot.players[position].was_hurt = NumericBool::True;
      snapshot.players[position].life = health;
    }
  }
}

void BasePlayer::change_state(std::unique_ptr<BaseState> new_state) {
  state = std::move(new_state);
}

void BasePlayer::move_right(uint8_t speed) {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_right(speed);
  if (state->can_move() && map.available_position(new_rectangle)) {
    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Right;
    is_moving = true;
    if (position != -1) {
      snapshot.players[position].position_x =
          rectangle.getTopLeftCorner().getX();
      snapshot.players[position].position_y =
          rectangle.getTopLeftCorner().getY();
      snapshot.players[position].facing_direction = FacingDirectionsIds::Right;
      snapshot.players[position].is_walking = NumericBool::True;
    }
  }
}

void BasePlayer::move_left(uint8_t speed) {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_left(speed);
  if (state->can_move() && map.available_position(new_rectangle)) {
    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Left;
    is_moving = true;
    if (position != -1) {
      snapshot.players[position].position_x =
          rectangle.getTopLeftCorner().getX();
      snapshot.players[position].position_y =
          rectangle.getTopLeftCorner().getY();
      snapshot.players[position].facing_direction = FacingDirectionsIds::Left;
      snapshot.players[position].is_walking = NumericBool::True;
    }
  }
}

void BasePlayer::run() {
  if ((position != -1 &&
       snapshot.players[position].is_jumping == NumericBool::True) ||
      (position != -1 &&
       snapshot.players[position].is_falling == NumericBool::True)) {
    return;
  }

  if (is_moving) {
    is_running = true;
    if (position != -1) {
      snapshot.players[position].is_running = NumericBool::True;
    }
  }
}

void BasePlayer::stop_running() {
  is_running = false;
  if (position != -1) {
    snapshot.players[position].is_running = NumericBool::False;
  }
}

void BasePlayer::jump() {
  if (snapshot.players[position].is_jumping == NumericBool::True ||
      snapshot.players[position].is_falling == NumericBool::True) {
    return;
  }

  if (positions_to_jump == 0) {
    positions_to_jump = MAX_JUMP;
    snapshot.players[position].is_jumping = NumericBool::True;
  }
}

void BasePlayer::stop_moving() {
  is_moving = false;
  if (position != -1) {
    snapshot.players[position].is_walking = NumericBool::False;
  }
}

void BasePlayer::get_intoxicated() {
  change_state(std::make_unique<Intoxicated>());
  if (position != -1) {
    snapshot.players[position].is_intoxicated = NumericBool::True;
  }
}

void BasePlayer::heal(uint8_t health_gain) {
  uint8_t new_health = health + health_gain;
  if (new_health > MAX_HEALTH) {
    health = MAX_HEALTH;
  } else {
    health = new_health;
  }
  if (position != -1) {
    snapshot.players[position].life = health;
  }
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
    return Bullet(GunsIds::Gun1, 0, 0, bullet_rectangle, facing_direction, map);
  }
}

bool BasePlayer::intersects(Rectangle rectangle) {
  return this->rectangle.intersects(rectangle);
}

bool BasePlayer::can_shoot() {
  return (state->can_shoot() && weapon->can_shoot());
}

bool BasePlayer::is_alive() { return health > 0; }

void BasePlayer::change_weapon(uint8_t weapon_id) {
  switch (weapon_id) {
  case GunsIds::Gun1:
    weapon = std::make_unique<InitialWeapon>(snapshot, position);
    snapshot.players[position].current_gun = GunsIds::Gun1;
    break;
  case GunsIds::Gun2:
    weapon = std::make_unique<Orb>(snapshot, orb_ammo, position);
    snapshot.players[position].current_gun = GunsIds::Gun2;
    break;
  }
}

BasePlayer::~BasePlayer() {
  // delete weapon;
  // delete state;
}
