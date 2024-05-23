#ifndef LORI
#define LORI

#include "base_player.h"
class Lori : public BasePlayer {
private:
public:
  Lori();
  void shoot() override;
  void run() override;
  void runFast() override;
  void jump() override;
  void specialAttack() override;
  ~Lori();
};

#endif