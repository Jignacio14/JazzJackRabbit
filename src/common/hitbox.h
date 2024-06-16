#ifndef HITBOX_H
#define HITBOX_H

class Hitbox {
private:
  // cppcheck-suppress unusedStructMember
  int width;
  // cppcheck-suppress unusedStructMember
  int height;

public:
  Hitbox(int width, int height);

  Hitbox(const Hitbox &other);
  Hitbox &operator=(const Hitbox &other);

  int getWidth() const;
  int getHeight() const;
  void setWidth(int width);
  void setHeight(int height);
};

#endif // HITBOX_H
