#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <cstdint>
struct MessageFormat {
public:
  uint16_t alives_count;
  uint16_t death_count;
  // true if enemy revived
  bool event_type;

  explicit MessageFormat(uint16_t alive_count, uint16_t death_count,
                         uint8_t event_type)
      : alives_count(alive_count), death_count(death_count),
        event_type(event_type) {}

  MessageFormat() : alives_count(0), death_count(0), event_type(false) {}

  bool hasDefaultFormat() {
    return this->event_type == false && this->alives_count == 0 &&
           this->death_count == 0;
  }
};

#endif
