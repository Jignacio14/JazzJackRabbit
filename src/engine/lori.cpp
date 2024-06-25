#include "lori.h"
#include "base_player.h"
#include <iostream>

Lori::Lori(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
           int position, ServerMap &map)
    : BasePlayer(player_id, player_name, snapshot, position, map),
      positions_to_jump_special(0) {}

void Lori::special_attack() {
  if (snapshot.players[position].is_jumping == NumericBool::True ||
      snapshot.players[position].is_falling == NumericBool::True ||
      health == 0) {
    return;
  }

  positions_to_jump_special = MAX_JUMP;
  doing_special_attack = true;
  lori_special_attack = true;
  snapshot.players[position].shot_special = NumericBool::True;
  update_special_attack();
}

void Lori::update_special_attack() {
  if (positions_to_jump_special > 0 && doing_special_attack) {
    Rectangle new_rectangle = rectangle;
    new_rectangle.move_up();
    bool is_jumping = map.available_position(new_rectangle);
    if (!is_jumping) {
      positions_to_jump_special = 0;
      snapshot.players[position].shot_special = NumericBool::False;
    } else {
      set_new_rectangle(new_rectangle);
      positions_to_jump_special--;
    }

  } else if (positions_to_jump_special == 0 && doing_special_attack) {
    doing_special_attack = false;
    lori_special_attack = false;
    snapshot.players[position].shot_special = NumericBool::False;
  }
}

void Lori::set_new_rectangle(Rectangle new_rectangle) {
  rectangle = new_rectangle;
  if (position != -1) {
    snapshot.players[position].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.players[position].position_y = rectangle.getTopLeftCorner().getY();
  }
}

Lori::~Lori() {}