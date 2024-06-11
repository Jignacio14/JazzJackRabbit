#include "base_player.h"

BasePlayer::BasePlayer(uint8_t player_id, const std::string &player_name,
                       Snapshot &snapshot, int position)
    : player_id(player_id), player_name(player_name), health(MAX_HEALTH),
      weapon(std::make_unique<InitialWeapon>()),
      state(std::make_unique<Alive>()),
      rectangle(Rectangle(Coordinates(100, 1100), Coordinates(60, 1050))),
      facing_direction(FacingDirectionsIds::Right), snapshot(snapshot),
      position(position) {}

int BasePlayer::find_position() {
  for (int i = 0; i < snapshot.sizePlayers; ++i) {
    if (snapshot.players[i].user_id == player_id) {
      return i;
    }
  }
  return -1;
}

void BasePlayer::update() { position = find_position(); }

void BasePlayer::receive_damage(uint8_t damage) {
  if (damage >= health) {
    health = 0;
    change_state(std::make_unique<Dead>());
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

void BasePlayer::move_right() {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_right();
  if (state->can_move() && map.available_position(new_rectangle)) {
    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Right;
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

void BasePlayer::move_left() {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_left();
  if (state->can_move() && map.available_position(new_rectangle)) {
    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Left;

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

void BasePlayer::stop_moving() {
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
    if (position != -1) {
      snapshot.players[position].life = health;
    }
  } else {
    health = new_health;
    if (position != -1) {
      snapshot.players[position].life = health;
    }
  }
}

BasePlayer::~BasePlayer() {
  // delete weapon;
  // delete state;
}
