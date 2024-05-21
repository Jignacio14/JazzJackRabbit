#include "thread.h"

Thread::Thread() : _keep_running(true), _is_alive(false) {}

void Thread::start() {
  this->_is_alive = true;
  this->_keep_running = true;
  this->thread = std::thread(&Thread::main, this);
}

void Thread::join() { this->thread.join(); }

void Thread::main() {
  try {
    this->run();
  } catch (const std::exception &err) {
    std::cerr << "Unexpected exception: " << err.what() << "\n";
  } catch (...) {
    std::cerr << "Unexpected exception: <unknown>\n";
  }

  this->_is_alive = false;
}

void Thread::stop() { this->_keep_running = false; }

bool Thread::is_alive() const { return this->_is_alive; }
