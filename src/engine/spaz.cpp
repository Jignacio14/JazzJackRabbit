#include "spaz.h"
#include <iostream>

Spaz::Spaz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
           int position, ServerMap &map)
    : BasePlayer(player_id, player_name, snapshot, position, map) {}

void Spaz::special_attack() {
  std::cout << "Spaz's special attack" << std::endl;
}

Spaz::~Spaz() {}