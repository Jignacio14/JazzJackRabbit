#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

class Logger {
private:
  // cppcheck-suppress unusedStructMember
  const std::string logs_filename;
  // cppcheck-suppress unusedStructMember
  const std::string time_format;
  // cppcheck-suppress unusedStructMember
  const std::string LEVEL_INFO;
  // cppcheck-suppress unusedStructMember
  const std::string LEVEL_WARNING;
  // cppcheck-suppress unusedStructMember
  const std::string LEVEL_ERROR;
  // cppcheck-suppress unusedStructMember
  std::ofstream logfile;

  /*
   *   If set to false in constructor the log calls to this class will not write
   * anything to the file, nor it will open the file
   */
  // cppcheck-suppress unusedStructMember
  bool is_activated;

  /*
   *   A mutex is used to ensure the logfile will be accessed by one thread at a
   * time
   */
  std::mutex mutex;

  /*
   *  Logger that logs events to a file. It can be used both in the server and
   * in the client with their respective methods. It is built using the
   * Singleton pattern. This way we use a single logger throughout the process.
   * That is why the constructor is hidden and the instance can be accessed with
   * the Logger::get_instance static method
   */
  Logger();

  /*
   *  Delete copy constructor and copy assignment operator.
   */
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  /*
   *  Delete move constructor and move assignment operator.
   */
  Logger(const Logger &&) = delete;
  Logger &operator=(const Logger &&) = delete;

  /*
   *  Closes the logfile
   */
  void close();

  /*
   *  Returns current time with the format defined by Logger::time_format
   */
  const std::string get_current_time();

  /*
   *  Writes in the file the logging output using the time format, the message
   * and the log level
   */
  void log(const std::string &log_level, const std::string &message);

public:
  /*
   *  Uses the Singleton design pattern
   *   Return the instance
   */
  static Logger &get_instance();

  /*
   *  It's a client method, so the log line will include the CLIENT keyword
   *  Logs the message with log level Logger::LEVEL_INFO
   */
  void client_info(const std::string &message);

  /*
   *  It's a client method, so the log line will include the CLIENT keyword
   *  Logs the message with log level Logger::LEVEL_WARNING
   */
  void client_warning(const std::string &message);

  /*
   *  It's a client method, so the log line will include the CLIENT keyword
   *  Logs the message with log level Logger::LEVEL_ERROR
   */
  void client_error(const std::string &message);

  /*
   *  It's a server method, so the log line will include the SERVER keyword
   *  Logs the message with log level Logger::LEVEL_INFO
   */
  void server_info(const std::string &message);

  /*
   *  It's a server method, so the log line will include the SERVER keyword
   *  Logs the message with log level Logger::LEVEL_WARNING
   */
  void server_warning(const std::string &message);

  /*
   *  It's a server method, so the log line will include the SERVER keyword
   *  Logs the message with log level Logger::LEVEL_ERROR
   */
  void server_error(const std::string &message);

  /*
   *  Closes the file before destroying member variables
   */
  ~Logger();
};

#endif // LOGGER_H
