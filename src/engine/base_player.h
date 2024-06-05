#ifndef BASE_PLAYER
#define BASE_PLAYER

#include <cstdint>
#include <string>
class BasePlayer {
private:
  // cppcheck-suppress unusedStructMember
  uint8_t player_id;
  // cppcheck-suppress unusedStructMember
  std::string player_name;

public:
  explicit BasePlayer(uint8_t player_id, std::string &player_name);
  void virtual shoot() = 0;
  void virtual run() = 0;
  void virtual runFast() = 0;
  void virtual jump() = 0;
  void virtual specialAttack() = 0;
};

#endif