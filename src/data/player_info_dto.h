#ifndef PLAYER_INFO
#define PLAYER_INFO

#include <cstdint>
#include <string>
#include <vector>

#define MAX_LEN 30

struct PlayerInfo {
  uint16_t str_len;
  char player_name[MAX_LEN];
  char game_name[MAX_LEN];
  uint8_t character_code;
} __attribute__((packed));

#endif // PLAYER_INFO
