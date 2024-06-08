#include "base_player.h"

BasePlayer(uint8_t player_id, std::string &player_name)
    : player_id(player_id), player_name(player_name), health(MAX_HEALTH),
      weapon(std::make_unique<InitialWeapon>()),
      state(std::make_unique<Alive>()) {}

void BasePlayer::receive_damage(uint16_t damage) {
  if (damage >= health) {
    health = 0;
    BaseState *dead = new Dead;
    change_state(dead);
  } else {
    health -= damage;
  }
}

void BasePlayer::change_state(BaseState *new_state) {
  if (state != nullptr) {
    delete state;
    state = new_state;
  }
}

BasePlayer::~BasePlayer() {
  // delete weapon;
  // delete state;
}
