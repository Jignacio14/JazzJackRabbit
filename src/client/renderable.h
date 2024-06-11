#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../common/coordinates.h"
#include "../common/snapshot_wrapper.h"
#include "../data/snapshot_dto.h"
#include <cstdint>
#include <string>

class Renderable {
private:
public:
  /**
   * Renders the Renderable based on an iterationNumber using its
   * own coordinates
   */
  virtual void render(int iterationNumber) = 0;

  /**
   * Renders the Renderable based on an iterationNumber using the
   * Coordinates passed as a parameter
   */
  virtual void render(int iterationNumber, Coordinates &coords) = 0;

  /**
   * Renders the Renderable based on an iterationNumber using its own
   * coordinates rendering from the left corner coordinates
   */
  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) = 0;

  virtual void updateByCoordsDelta(int deltaX, int deltaY){};

  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection){};

  virtual void update(SnapshotWrapper &snapshot){};

  virtual uint8_t getId() const = 0;

  virtual ~Renderable(){};
};

#endif // RENDERABLE_H
