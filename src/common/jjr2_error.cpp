#include "jjr2_error.h"

#include <iostream>

JJR2Error::JJR2Error(const std::string &base_message,
                     const int32_t &line_number, const std::string &module)
    : base_message(base_message), line_number(line_number), module(module) {
  this->final_message = "[JazzJackrabbit2Error]" + base_message +
                        " Module: " + module +
                        ". Line: " + std::to_string(line_number);
}

const char *JJR2Error::what() const noexcept {
  return this->final_message.c_str();
}
