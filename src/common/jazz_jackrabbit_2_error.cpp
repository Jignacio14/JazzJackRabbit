#include "jazz_jackrabbit_2_error.h"

#include <iostream>

JazzJackrabbit2Error::JazzJackrabbit2Error(const std::string &base_message,
                                           const int32_t &line_number,
                                           const std::string &module)
    : base_message(base_message), line_number(line_number), module(module) {
  this->final_message = "[JazzJackrabbit2Error]" + base_message +
                        " Module: " + module +
                        ". Line: " + std::to_string(line_number);
}

const char *JazzJackrabbit2Error::what() const noexcept {
  return this->final_message.c_str();
}
