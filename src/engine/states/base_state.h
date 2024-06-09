
#ifndef JAZZJACKRABBIT_BASE_STATE_H
#define JAZZJACKRABBIT_BASE_STATE_H

class BaseState {

public:
  bool virtual can_move() = 0;
};

#endif // JAZZJACKRABBIT_BASE_STATE_H
