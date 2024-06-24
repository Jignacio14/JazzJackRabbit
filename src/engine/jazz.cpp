#include "jazz.h"
#include "base_player.h"
#include <sys/types.h>

Jazz::Jazz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
           int position, ServerMap &map)
    : BasePlayer(player_id, player_name, snapshot, position, map) {}

void Jazz::special_attack() {
  if (health > 0) {
    positions_to_jump = MAX_JUMP;
    snapshot.players[position].shot_special = NumericBool::True;
  }
}

Jazz::~Jazz() {}