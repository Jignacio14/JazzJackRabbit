#ifndef SERIALIZER
#define SERIALIZER

#include "server_game_info_dto.h"
#include <string>
#include <sys/types.h>
class Serializer {
private:
public:
  explicit Serializer();

  GameInfoDto serializeGameInfo(const std::string &name,
                                const u_int16_t &count);
};

#endif