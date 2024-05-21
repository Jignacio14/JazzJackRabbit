#include "random_string_generator.h"

#include <chrono>
#include <random>

RandomStringGenerator::RandomStringGenerator() {}

const uint32_t RandomStringGenerator::get_current_time_ms() {
  auto current_time = std::chrono::system_clock::now();
  auto current_time_ms =
      std::chrono::time_point_cast<std::chrono::milliseconds>(current_time);
  auto current_time_ms_value = current_time_ms.time_since_epoch().count();

  return current_time_ms_value;
}

const int32_t RandomStringGenerator::get_random_number(int32_t min_number,
                                                       int32_t max_number) {
  std::random_device random_device;
  std::mt19937 random_generator(random_device());
  std::uniform_int_distribution<> distribution(min_number, max_number);
  return distribution(random_generator);
}

const std::string RandomStringGenerator::get_random_string() {
  uint32_t current_time_ms = RandomStringGenerator::get_current_time_ms();
  int32_t random_number =
      RandomStringGenerator::get_random_number(0, 100000000);
  return std::to_string(current_time_ms) + "-" + std::to_string(random_number);
}
