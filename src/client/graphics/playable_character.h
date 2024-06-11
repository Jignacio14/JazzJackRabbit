#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "../../common/coordinates.h"
#include "../renderable.h"
#include <string>

class PlayableCharacter : public Renderable {
private:
public:
  virtual void render(int iterationNumber) override = 0;
  virtual void render(int iterationNumber, Coordinates &coords) override = 0;
  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override = 0;
  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection) override = 0;
  virtual void update(SnapshotWrapper &snapshot) override = 0;

  virtual uint8_t getId() const override = 0;

  virtual Coordinates getCoords() = 0;
  virtual void setX(int x) = 0;
  virtual void setY(int y) = 0;
};

#endif // PLAYABLE_CHARACTER_H