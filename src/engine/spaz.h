
#ifndef SPAZ
#define SPAZ

#include "base_player.h"
class Spaz : public BasePlayer {
private:
public:
  Spaz();
  void shoot() override;
  void run() override;
  void runFast() override;
  void jump() override;
  void specialAttack() override;
  ~Spaz();
};
#endif