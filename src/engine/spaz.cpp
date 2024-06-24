#include "spaz.h"
#include "base_player.h"
#include <iostream>

#define MAX_POSITIONS 100

Spaz::Spaz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
           int position, ServerMap &map)
    : BasePlayer(player_id, player_name, snapshot, position, map),
      positions_to_move(0) {}

void Spaz::special_attack() {
  doing_special_attack = true;
  snapshot.players[position].shot_special = NumericBool::True;
  this->positions_to_move = MAX_POSITIONS;
  execute_special_attack();
}

void Spaz::execute_special_attack() {
  Rectangle new_rectangle = rectangle;
  if (facing_direction == FacingDirectionsIds::Left) {
    new_rectangle.move_left(RUNNING_SPEED);
    if (map.available_position(new_rectangle)) {
      set_new_rectangle(new_rectangle);
    }
  } else {
    new_rectangle.move_right(RUNNING_SPEED);
    if (map.available_position(new_rectangle)) {
      set_new_rectangle(new_rectangle);
    }
  }
}

void Spaz::set_new_rectangle(Rectangle new_rectangle) {
  rectangle = new_rectangle;
  if (position != -1) {
    snapshot.players[position].position_x = rectangle.getTopLeftCorner().getX();
    snapshot.players[position].position_y = rectangle.getTopLeftCorner().getY();
  }
}

void Spaz::update_special_attack() {
  if (doing_special_attack) {
    if (positions_to_move > 0) {
      execute_special_attack();
      positions_to_move--;
    }

    if (positions_to_move == 0) {
      doing_special_attack = false;
      snapshot.players[position].shot_special = NumericBool::False;
    }
  }
}

Spaz::~Spaz() {}