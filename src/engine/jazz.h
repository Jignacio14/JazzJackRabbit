#ifndef JAZZ
#define JAZZ

#include "base_player.h"
#include <cstdint>
class Jazz : public BasePlayer {
private:
public:
  explicit Jazz(uint8_t player_id, std::string &player_name);
  void shoot() override;
  void run() override;
  void runFast() override;
  void jump() override;
  void specialAttack() override;
  ~Jazz();
};

#endif