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

#define MAX_JUMP 200
#define WALKING_SPEED 1
#define RUNNING_SPEED 3

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
  // cppcheck-suppress unusedStructMember
  int position;
  // cppcheck-suppress unusedStructMember
  int positions_to_jump;
  // cppcheck-suppress unusedStructMember
  bool is_moving;
  // cppcheck-suppress unusedStructMember
  bool is_running;

  bool move_down();
  bool move_up();
  int find_position();
  void change_state(std::unique_ptr<BaseState> new_state);

public:
  BasePlayer(uint8_t player_id, const std::string &player_name,
             Snapshot &snapshot, int position);
  // void virtual shoot() = 0;
  // void virtual run() = 0;
  // void virtual runFast() = 0;
  // void virtual specialAttack() = 0;

  void update();
  void receive_damage(uint8_t damage);
  void get_intoxicated();
  void heal(uint8_t health_gain);

  void move_right(uint8_t speed);
  void move_left(uint8_t speed);
  void stop_moving();
  void jump();
  void run();
  void stop_running();

  ~BasePlayer();
};

#endif