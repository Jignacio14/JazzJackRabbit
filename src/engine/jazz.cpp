#include "jazz.h"
#include "base_player.h"
#include <sys/types.h>

Jazz::Jazz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
           int position, ServerMap &map)
    : BasePlayer(player_id, player_name, snapshot, position, map) {}

void Jazz::special_attack() { jump(); }

Jazz::~Jazz() {}