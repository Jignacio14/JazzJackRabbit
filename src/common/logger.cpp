#include "logger.h"

#include <unistd.h>

#include "jazz_jackrabbit_2_error.h"

Logger &Logger::get_instance() {
  static Logger logger;
  return logger;
}

Logger::Logger()
    : logs_filename("./process.logs"), time_format("[%d-%m-%Y %H:%M:%S] "),
      LEVEL_INFO("INFO"), LEVEL_WARNING("WARNING"), LEVEL_ERROR("ERROR"),
      is_activated(true) {
  if (!is_activated) {
    return;
  }
  this->logfile.open(this->logs_filename, std::ios::app);
  if (!this->logfile.is_open()) {
    throw JazzJackrabbit2Error(
        "Failed to open log file when initializing Logger class.", __LINE__,
        __FILE__);
  }
}

const std::string Logger::get_current_time() {
  std::time_t current_time = std::time(nullptr);
  char timestamp[50];
  std::strftime(timestamp, sizeof(timestamp), this->time_format.c_str(),
                std::localtime(&current_time));
  return timestamp;
}

void Logger::log(const std::string &log_level, const std::string &message) {
  std::unique_lock<std::mutex> lock(this->mutex);
  if (!is_activated) {
    return;
  }
  const std::string timestamp = this->get_current_time();
  const pid_t pid = getpid();
  this->logfile << "[" + log_level + "] " << timestamp
                << "[" + std::to_string(pid) + "] " << message << std::endl;
}

void Logger::client_info(const std::string &message) {
  this->log(this->LEVEL_INFO, "[CLIENT] " + message);
}

void Logger::client_warning(const std::string &message) {
  this->log(this->LEVEL_WARNING, "[CLIENT] " + message);
}

void Logger::client_error(const std::string &message) {
  this->log(this->LEVEL_ERROR, "[CLIENT] " + message);
}

void Logger::server_info(const std::string &message) {
  this->log(this->LEVEL_INFO, "[SERVER] " + message);
}

void Logger::server_warning(const std::string &message) {
  this->log(this->LEVEL_WARNING, "[SERVER] " + message);
}

void Logger::server_error(const std::string &message) {
  this->log(this->LEVEL_ERROR, "[SERVER] " + message);
}

void Logger::close() {
  if (!is_activated) {
    return;
  }
  if (this->logfile.is_open()) {
    this->logfile.close();
  }
}

Logger::~Logger() { this->close(); }
