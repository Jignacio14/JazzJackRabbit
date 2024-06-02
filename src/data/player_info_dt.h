#ifndef PLAYER_INFO
#define PLAYER_INFO

#include <cstdint>
#include <string>
struct PlayerInfo {
  std::string player_name;
  std::string game_name;
  uint8_t character_code;
  PlayerInfo(std::string player_name, std::string game_name,
             uint8_t character_code)
      : player_name(player_name), game_name(game_name),
        character_code(character_code) {}
};

#endif