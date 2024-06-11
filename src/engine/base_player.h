#ifndef BASE_PLAYER
#define BASE_PLAYER

#include "../common/rectangle.h"
#include "../data/convention.h"
#include "../data/snapshot_dto.h"
#include "server_map.h"
#include "states/alive.h"
#include "states/dead.h"
#include "states/intoxicated.h"
#include "weapons/base_weapon.h"
#include "weapons/initial_weapon.h"
#include <cstdint>
#include <memory>
#include <string>

#define MAX_HEALTH 100

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
  Rectangle rectangle;
  // cppcheck-suppress unusedStructMember
  uint8_t facing_direction;

  ServerMap map;
  // cppcheck-suppress unusedStructMember
  Snapshot &snapshot;

public:
  BasePlayer(uint8_t player_id, const std::string &player_name,
             Snapshot &snapshot);
  // void virtual shoot() = 0;
  // void virtual run() = 0;
  // void virtual runFast() = 0;
  // void virtual jump(Snapshot &snapshot) = 0;
  // void virtual specialAttack(Snapshot &snapshot) = 0;

  void receive_damage(uint8_t damage);
  void change_state(std::unique_ptr<BaseState> new_state);
  void get_intoxicated();
  void heal(uint8_t health_gain);

  void move_right();
  void move_left();
  void stop_moving();

  ~BasePlayer();
};

#endif