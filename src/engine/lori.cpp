#include "lori.h"
#include <iostream>

Lori::Lori(uint8_t player_id, std::string &player_name, Snapshot &snapshot)
    : BasePlayer(player_id, player_name, snapshot) {}

Lori::~Lori() {}