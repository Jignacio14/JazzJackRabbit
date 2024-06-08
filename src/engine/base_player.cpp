#include "base_player.h"

BasePlayer::BasePlayer(uint8_t player_id, const std::string &player_name)
    : player_id(player_id), player_name(player_name), health(MAX_HEALTH),
      weapon(std::make_unique<InitialWeapon>()),
      state(std::make_unique<Alive>()) {}

void BasePlayer::receive_damage(uint16_t damage) {
  if (damage >= health) {
    health = 0;
    change_state(std::make_unique<Dead>());
  } else {
    health -= damage;
  }
}

void BasePlayer::change_state(std::unique_ptr<BaseState> new_state) {
  state = std::move(new_state);
  ;
}

BasePlayer::~BasePlayer() {
  // delete weapon;
  // delete state;
}
