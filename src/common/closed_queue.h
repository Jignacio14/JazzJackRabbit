#ifndef CLOSED_QUEUE_H
#define CLOSED_QUEUE_H

#include <stdexcept>

class ClosedQueue : public std::runtime_error {
public:
  /*
   *   Exception that indicates when a Queue is closed and an operation was
   * performed over it
   */
  explicit ClosedQueue(const int line_number);
};

#endif // CLOSED_QUEUE_H
