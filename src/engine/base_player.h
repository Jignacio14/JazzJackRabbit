#ifndef BASE_PLAYER
#define BASE_PLAYER

#include "states/alive.h"
#include "states/dead.h"
#include "weapons/base_weapon.h"
#include "weapons/initial_weapon.h"
#include <cstdint>
#include <memory>
#include <string>

#define MAX_HEALTH 1000

class BasePlayer {
private:
  // cppcheck-suppress unusedStructMember
  uint8_t player_id;
  // cppcheck-suppress unusedStructMember
  std::string player_name;
  // cppcheck-suppress unusedStructMember
  uint16_t health;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<BaseWeapon> weapon;
  // cppcheck-suppress unusedStructMember
  std::unique_ptr<BaseState> state;

public:
  BasePlayer(uint8_t player_id, const std::string &player_name);
  void virtual shoot() = 0;
  void virtual run() = 0;
  void virtual runFast() = 0;
  void virtual jump() = 0;
  void virtual specialAttack() = 0;

  void receive_damage(uint16_t damage);
  void change_state(std::unique_ptr<BaseState> new_state);

  ~BasePlayer();
};

#endif