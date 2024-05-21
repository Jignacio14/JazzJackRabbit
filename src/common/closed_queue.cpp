#include "closed_queue.h"

#include <string>

ClosedQueue::ClosedQueue(const int line_number)
    : std::runtime_error(std::string("The queue is closed. Module ") +
                         __FILE__ + std::string(". Line: ") +
                         std::to_string(line_number)) {}
