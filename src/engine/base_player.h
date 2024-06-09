#ifndef BASE_PLAYER
#define BASE_PLAYER

#include "../data/convention.h"
#include "states/alive.h"
#include "states/dead.h"
#include "states/intoxicated.h"
#include "weapons/base_weapon.h"
#include "weapons/initial_weapon.h"
#include <cstdint>
#include <memory>
#include <string>

#define MAX_HEALTH 100
#define INITIAL_POS_X 0
#define INITIAL_POS_Y 0

class BasePlayer {
private:
  // cppcheck-suppress unusedStructMember
  uint8_t player_id;
  // cppcheck-suppress unusedStructMember
  std::string player_name;
  // cppcheck-suppress unusedStructMember
  uint8_t health;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<BaseWeapon> weapon;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<BaseState> state;
  // cppcheck-suppress unusedStructMember
  int16_t position_x;
  // cppcheck-suppress unusedStructMember
  int16_t position_y;
  // cppcheck-suppress unusedStructMember
  uint8_t facing_direction;

public:
  BasePlayer(uint8_t player_id, const std::string &player_name);
  void virtual shoot() = 0;
  void virtual run() = 0;
  void virtual runFast() = 0;
  void virtual jump() = 0;
  void virtual specialAttack() = 0;

  void receive_damage(uint8_t damage);
  void change_state(std::unique_ptr<BaseState> new_state);

  void move_right();
  void move_left();

  void get_intoxicated();
  void heal(uint8_t health_gain);

  ~BasePlayer();
};

#endif