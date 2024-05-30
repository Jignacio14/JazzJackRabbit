#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable {
private:
public:
  virtual void render(int it) = 0;
  // virtual void setRate(double rate) = 0;
  virtual ~Renderable(){};
};

#endif // RENDERABLE_H
