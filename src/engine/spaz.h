
#ifndef SPAZ
#define SPAZ

#include "base_player.h"
class Spaz : public BasePlayer {
private:
public:
  explicit Spaz(uint8_t player_id, std::string &player_name,
                Snapshot &snapshot);

  ~Spaz();
};
#endif