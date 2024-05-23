#ifndef BASE_PLAYER
#define BASE_PLAYER

class BasePlayer {
private:
public:
  void virtual shoot() = 0;
  void virtual run() = 0;
  void virtual runFast() = 0;
  void virtual jump() = 0;
  void virtual specialAttack() = 0;
};

#endif