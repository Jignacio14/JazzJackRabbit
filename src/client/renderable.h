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
   * Renders the Renderable based on an iterationNumber using its own
   * coordinates rendering from the left corner coordinates
   */
  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) = 0;

  virtual void update(SnapshotWrapper &snapshot,
                      const Coordinates &leftCorner){};

  virtual bool shouldDelete() const { return false; };

  virtual uint8_t getId() const = 0;

  virtual ~Renderable(){};
};

#endif // RENDERABLE_H
