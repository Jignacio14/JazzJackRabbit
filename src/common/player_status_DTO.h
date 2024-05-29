#ifndef JAZZJACKRABBIT_PLAYER_STATUS_DTO_H
#define JAZZJACKRABBIT_PLAYER_STATUS_DTO_H

#include <cstdint>
#include <iostream>

struct PlayerStatusDTO {
  // cppcheck-suppress unusedStructMember
  uint8_t mov_h;
  // uint8_t mov_h;
  // etc

  PlayerStatusDTO();
};

#endif // JAZZJACKRABBIT_PLAYER_STATUS_DTO_H
