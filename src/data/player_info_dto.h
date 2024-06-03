#ifndef PLAYER_INFO
#define PLAYER_INFO

#include <cstdint>
#include <string>
#include <vector>
struct PlayerInfo {
  std::vector<char> player_name;
  std::vector<char> game_name;
  uint8_t character_code;
  PlayerInfo(const std::vector<char> &player_name,
             const std::vector<char> &game_name, const uint8_t &character_code)
      : player_name(player_name), game_name(game_name),
        character_code(character_code) {}
  PlayerInfo() : player_name(), game_name(), character_code(0) {}
};

#endif