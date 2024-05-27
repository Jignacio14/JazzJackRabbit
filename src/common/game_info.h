#ifndef GAME_INFO_DTO
#define GAME_INFO_DTO

#include <cstdint>
#include <vector>

struct GameInfoDto {
  // cppcheck-suppress unusedStructMember
  uint16_t str_len;
  // cppcheck-suppress unusedStructMember
  std::vector<char> game_name;
  // cppcheck-suppress unusedStructMember
  uint16_t player_count;
} __attribute__((packed));
#endif