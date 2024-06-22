#include "./disconnection_exception.h"

#include <iostream>

const char ERROR_MESSAGE[] = "Disconnection detected.";

DisconnectionException::DisconnectionException(const int32_t &line_number,
                                               const std::string &module)
    : message(ERROR_MESSAGE), line_number(line_number), module(module) {
  this->message = this->message + " Module: " + module +
                  ". Line: " + std::to_string(line_number);
}

const char *DisconnectionException::what() const noexcept {
  return this->message.c_str();
}
