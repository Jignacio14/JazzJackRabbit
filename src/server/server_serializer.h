#ifndef SERIALIZER
#define SERIALIZER

#include "../common/game_info.h"
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