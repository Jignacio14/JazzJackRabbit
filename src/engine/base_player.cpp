#include "base_player.h"
#include <iostream>

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
  } else {
    health -= damage;
  }
}

void BasePlayer::change_state(std::unique_ptr<BaseState> new_state) {
  state = std::move(new_state);
}

void BasePlayer::move_right() {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_right();
  std::cout << "Moving Right afuera del if"
            << "\n";
  if (state->can_move() && map.available_position(new_rectangle)) {
    std::cout << "Moving Right"
              << "\n";

    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Right;

    for (int i = 0; i < snapshot.sizePlayers; ++i) {
      if (snapshot.players[i].user_id == player_id) {
        snapshot.players[i].position_x = rectangle.getTopLeftCorner().getX();
        snapshot.players[i].position_y = rectangle.getTopLeftCorner().getY();
        snapshot.players[i].facing_direction = FacingDirectionsIds::Right;
        break;
      }
    }
  }
}

void BasePlayer::move_left() {
  Rectangle new_rectangle = rectangle;
  new_rectangle.move_left();
  std::cout << "Moving Left afuera del if"
            << "\n";
  if (state->can_move() && map.available_position(new_rectangle)) {
    std::cout << "Moving Left"
              << "\n";
    rectangle = new_rectangle;
    facing_direction = FacingDirectionsIds::Left;

    for (int i = 0; i < snapshot.sizePlayers; ++i) {
      if (snapshot.players[i].user_id == player_id) {
        snapshot.players[i].position_x = rectangle.getTopLeftCorner().getX();
        snapshot.players[i].position_y = rectangle.getTopLeftCorner().getY();
        snapshot.players[i].facing_direction = FacingDirectionsIds::Left;
        break;
      }
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
