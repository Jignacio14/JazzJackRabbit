#include "base_player.h"

BasePlayer::BasePlayer(uint8_t player_id, const std::string &player_name)
    : player_id(player_id), player_name(player_name), health(MAX_HEALTH),
      weapon(std::make_unique<InitialWeapon>()),
      state(std::make_unique<Alive>()), position_x(INITIAL_POS_X),
      position_y(INITIAL_POS_Y), facing_direction(FacingDirectionsIds::Right) {}

void BasePlayer::receive_damage(uint8_t damage) {
  if (damage >= health) {
    health = 0;
    change_state(std::make_unique<Dead>());
  } else {
    health -= damage;
  }
}

void BasePlayer::change_state(std::unique_ptr<BaseState> new_state) {
  state = std::move(new_state);
}

void BasePlayer::move_right() {
  // Probablemente el player necesite tener una referencia al mapa y chequear
  // que se mueva a una posición válida.
  if (state->can_move()) {
    position_x += 1;
    facing_direction = FacingDirectionsIds::Right;
  }
}

void BasePlayer::move_left() {
  // Probablemente el player necesite tener una referencia al mapa y chequear
  // que se mueva a una posición válida.
  if (state->can_move()) {
    position_x -= 1;
    facing_direction = FacingDirectionsIds::Left;
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
