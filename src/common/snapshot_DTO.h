
#ifndef JAZZJACKRABBIT_SNAPSHOT_H
#define JAZZJACKRABBIT_SNAPSHOT_H

#include <cstdint>

struct Snapshot {
  // cppcheck-suppress unusedStructMember
  uint8_t enemies_alive;
  // etc

  Snapshot();
};

#endif // JAZZJACKRABBIT_SNAPSHOT_H
