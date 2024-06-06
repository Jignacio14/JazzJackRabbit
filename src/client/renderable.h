#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>

class Renderable {
private:
public:
  virtual void render(int it) = 0;
  virtual void updateByCoords(int x, int y){};
  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection){};
  // virtual void setRate(double rate) = 0;
  virtual ~Renderable(){};
};

#endif // RENDERABLE_H
