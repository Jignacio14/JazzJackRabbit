#ifndef LORI
#define LORI

#include "base_player.h"
class Lori : public BasePlayer {
private:
public:
  explicit Lori(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
                int position, ServerMap &map);

  ~Lori();
};

#endif