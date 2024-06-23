#ifndef GLOBAL_COUNTER_H
#define GLOBAL_COUNTER_H

#include <cstdint>

class GlobalCounter {

private:
  // cppcheck-suppress unusedStructMember
  uint32_t counter;

  GlobalCounter();

  GlobalCounter(const GlobalCounter &) = delete;
  GlobalCounter &operator=(const GlobalCounter &) = delete;

public:
  static GlobalCounter &getInstance();
  uint32_t getNextID();
};

#endif // GLOBAL_COUNTER_H
