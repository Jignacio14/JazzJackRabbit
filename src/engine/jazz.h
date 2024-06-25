#ifndef JAZZ
#define JAZZ

#include "base_player.h"
#include <cstdint>
class Jazz : public BasePlayer {
private:
public:
  Jazz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
       int position, ServerMap &map);

  void special_attack() override;
  void update_special_attack() override;
  ~Jazz();
};

#endif