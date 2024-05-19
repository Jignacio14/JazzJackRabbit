
#ifndef JAZZJACKRABBIT_STOPITERATION_H
#define JAZZJACKRABBIT_STOPITERATION_H

#include <stdexcept>

class StopIteration : public std::runtime_error {
public:
    StopIteration() : std::runtime_error("StopIteration") {}
};

#endif //JAZZJACKRABBIT_STOPITERATION_H
