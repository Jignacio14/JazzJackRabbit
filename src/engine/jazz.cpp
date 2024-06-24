#include "jazz.h"
#include "base_player.h"
#include <iostream>
#include <sys/types.h>

Jazz::Jazz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
           int position, ServerMap &map)
    : BasePlayer(player_id, player_name, snapshot, position, map) {}

void Jazz::special_attack() {
  if (health > 0) {
    positions_to_jump = MAX_JUMP;
    doing_special_attack = true;
    snapshot.players[position].shot_special = NumericBool::True;
  }
}

void Jazz::update_special_attack() {
  if (positions_to_jump > 0 && doing_special_attack) {
    snapshot.players[position].shot_special = NumericBool::True;
  } else {
    snapshot.players[position].shot_special = NumericBool::False;
    doing_special_attack = false;
  }
}

Jazz::~Jazz() {}