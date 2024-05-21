#ifndef THREAD_H_
#define THREAD_H_

#include <atomic>
#include <iostream>
#include <thread>

#include "runnable.h"

class Thread : public Runnable {
private:
  std::thread thread;

protected:
  // Subclasses that inherit from Thread will have access to these
  // flags, mostly to control how Thread::run() will behave
  std::atomic<bool> _keep_running;
  std::atomic<bool> _is_alive;

public:
  Thread();

  void start() override;

  void join() override;

  void main();

  // Note: it is up to the subclass to make something meaningful to
  // really stop the thread. The Thread::run() may be blocked and/or
  // it may not read _keep_running.
  void stop() override;

  bool is_alive() const override;

  virtual void run() = 0;
  virtual ~Thread() {}

  Thread(const Thread &) = delete;
  Thread &operator=(const Thread &) = delete;

  Thread(Thread &&other) = delete;
  Thread &operator=(Thread &&other) = delete;
};

#endif // THREAD_H_
