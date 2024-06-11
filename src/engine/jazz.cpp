#include "jazz.h"
#include "base_player.h"
#include <iostream>
#include <sys/types.h>

Jazz::Jazz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
           int position)
    : BasePlayer(player_id, player_name, snapshot, position) {}

Jazz::~Jazz() {}