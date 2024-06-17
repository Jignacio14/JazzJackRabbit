#ifndef SERIALIZER
#define SERIALIZER

#include "../common/game_info.h"
#include "../data/snapshot_dto.h"
#include <string>
#include <sys/types.h>

class Serializer {
private:
  double htond(double rawValue);

public:
  explicit Serializer();

  GameInfoDto serializeGameInfo(const std::string &name,
                                const u_int16_t &count);

  Snapshot serializeSnapshot(const Snapshot &snapshot);
};

#endif