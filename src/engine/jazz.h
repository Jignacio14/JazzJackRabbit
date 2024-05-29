#ifndef JAZZ
#define JAZZ

#include "base_player.h"
class Jazz : public BasePlayer {
private:
public:
  Jazz();
  void shoot() override;
  void run() override;
  void runFast() override;
  void jump() override;
  void specialAttack() override;
  ~Jazz();
};

#endif