#ifndef LORI
#define LORI

#include "base_player.h"
class Lori : public BasePlayer {
private:
  // cppcheck-suppress unusedStructMember
  int positions_to_jump_special;

  void set_new_rectangle(Rectangle new_rectangle);

public:
  explicit Lori(uint8_t player_id, std::string &player_name, Snapshot &snapshot,
                int position, ServerMap &map);

  void special_attack() override;
  void update_special_attack() override;
  ~Lori();
};

#endif