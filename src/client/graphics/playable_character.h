#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "../renderable.h"
#include <string>

class PlayableCharacter : public Renderable {
private:
public:
  virtual void render(int it) override = 0;
};

#endif // PLAYABLE_CHARACTER_H