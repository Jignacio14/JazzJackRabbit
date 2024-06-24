
#ifndef JAZZJACKRABBIT_INTOXICATED_H
#define JAZZJACKRABBIT_INTOXICATED_H

#include "base_state.h"

class Intoxicated : public BaseState {

public:
  bool can_move() override;
  bool can_shoot() override;
  bool can_jump() override;
};

#endif // JAZZJACKRABBIT_INTOXICATED_H
