#include "spaz.h"
#include <iostream>

Spaz::Spaz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
           int position)
    : BasePlayer(player_id, player_name, snapshot, position) {}

Spaz::~Spaz() {}