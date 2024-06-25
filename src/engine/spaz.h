
#ifndef SPAZ
#define SPAZ

#include "base_player.h"
class Spaz : public BasePlayer {
private:
  // cppcheck-suppress unusedStructMember
  int positions_to_move;

  void execute_special_attack();
  void set_new_rectangle(Rectangle new_rectangle);

public:
  explicit Spaz(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
                int position, ServerMap &map);

  void special_attack() override;
  void update_special_attack() override;
  ~Spaz();
};
#endif