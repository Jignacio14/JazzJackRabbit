#ifndef GAME_INFO_DTO
#define GAME_INFO_DTO

#include <cstdint>
#include <vector>

#define MAX_LEN 12

struct GameInfoDto {
  // cppcheck-suppress unusedStructMember
  uint16_t str_len;
  // cppcheck-suppress unusedStructMember
  char game_name[MAX_LEN];
  // cppcheck-suppress unusedStructMember
  uint16_t player_count;
} __attribute__((packed));
#endif