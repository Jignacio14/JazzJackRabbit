#include "global_counter.h"

GlobalCounter::GlobalCounter() : counter(0) {}

GlobalCounter &GlobalCounter::getInstance() {
  static GlobalCounter instance;
  return instance;
}

uint32_t GlobalCounter::getNextID() { return ++counter; }
