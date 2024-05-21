#ifndef RANDOM_STRING_GENERATOR_H
#define RANDOM_STRING_GENERATOR_H

#include <cstdint>
#include <string>

class RandomStringGenerator {
private:
  /*
   *   Returns the current UNIX timestamp in miliseconds
   */
  static const uint32_t get_current_time_ms();

  /*
   *   Returns a pseudorandom number inbetween it's bouning parameters
   */
  static const int32_t get_random_number(int32_t min_number,
                                         int32_t max_number);

public:
  /*
   *   A static class that serves as a utility tool to generate pseudorandom
   * strings It does not need to be instantiated.
   */
  RandomStringGenerator();

  /*
   *   Return a string with the format '%TIME-%RANDOM' where %TIME is the result
   * of calling RandomStringGenerator::get_current_time_ms and %RANDOM is the
   * result of calling RandomStringGenerator::get_random_number
   */
  static const std::string get_random_string();
};

#endif // RANDOM_STRING_GENERATOR_H
