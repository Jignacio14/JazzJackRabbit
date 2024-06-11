#include "base_player.h"

BasePlayer::BasePlayer(uint8_t player_id, const std::string &player_name,
                       Snapshot &snapshot)
    : player_id(player_id), player_name(player_name), health(MAX_HEALTH),
      weapon(std::make_unique<InitialWeapon>()),
      state(std::make_unique<Alive>()),
      rectangle(Rectangle(Coordinates(100, 1100), Coordinates(60, 1050))),
      facing_direction(FacingDirectionsIds::Right), snapshot(snapshot) {}

void BasePlayer::receive_damage(uint8_t damage) {
  if (damage >= health) {
    health = 0;
    change_state(std::make_unique<Dead>());
    for (int i = 0; i < snapshot.sizePlayers; ++i) {
      if (snapshot.players[i].user_id == player_id) {
        snapshot.players[i].is_dead = NumericBool::True;
        break;
      }
    }
  } else {
    health -= damage;
    for (int i = 0; i < snapshot.sizePlayers; ++i) {
      if (snapshot.players[i].user_id == player_id) {
        snapshot.players[i].was_hurt == NumericBool::True;
        snapshot.players[i].life = health;
        break;
      }
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

    for (int i = 0; i < snapshot.sizePlayers; ++i) {
      if (snapshot.players[i].user_id == player_id) {
        snapshot.players[i].position_x = rectangle.getTopLeftCorner().getX();
        snapshot.players[i].position_y = rectangle.getTopLeftCorner().getY();
        snapshot.players[i].facing_direction = FacingDirectionsIds::Right;
        snapshot.players[i].is_walking = NumericBool::True;
        break;
      }
    }
  }
}

void BasePlayer::move_left() {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_left();
  if (state->can_move() && map.available_position(new_rectangle)) {
    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Left;

    for (int i = 0; i < snapshot.sizePlayers; ++i) {
      if (snapshot.players[i].user_id == player_id) {
        snapshot.players[i].position_x = rectangle.getTopLeftCorner().getX();
        snapshot.players[i].position_y = rectangle.getTopLeftCorner().getY();
        snapshot.players[i].facing_direction = FacingDirectionsIds::Left;
        snapshot.players[i].is_walking = NumericBool::True;
        break;
      }
    }
  }
}

void BasePlayer::stop_moving() {
  for (int i = 0; i < snapshot.sizePlayers; ++i) {
    if (snapshot.players[i].user_id == player_id) {
      snapshot.players[i].is_walking = NumericBool::False;
      break;
    }
  }
}

void BasePlayer::get_intoxicated() {
  change_state(std::make_unique<Intoxicated>());
}

void BasePlayer::heal(uint8_t health_gain) {
  uint8_t new_health = health + health_gain;
  if (new_health > MAX_HEALTH) {
    health = MAX_HEALTH;
  } else {
    health = new_health;
  }
}

BasePlayer::~BasePlayer() {
  // delete weapon;
  // delete state;
}
