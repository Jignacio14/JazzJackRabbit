#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "../renderable.h"
#include <string>

class PlayableCharacter : public Renderable {
private:
public:
  virtual void render(int iterationNumber) override = 0;
  virtual void render(int iterationNumber, Coordinates &coords) override = 0;
  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override = 0;
};

#endif // PLAYABLE_CHARACTER_H