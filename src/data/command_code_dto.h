#ifndef COMMAND_DATA
#define COMMAND_DATA

#include <cstdint>

struct CommandCodeDto {
  // cppcheck-suppress unusedStructMember
  uint8_t player_id;
  // cppcheck-suppress unusedStructMember
  uint8_t code;
  // cppcheck-suppress unusedStructMember
  uint8_t data;
};
__attribute__((packed));

#endif