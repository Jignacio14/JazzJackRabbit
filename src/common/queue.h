#ifndef QUEUE_H_
#define QUEUE_H_

#include <climits>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <string>

#include "closed_queue.h"

/*
 * Multiproducer/Multiconsumer Blocking Queue (MPMC)
 *
 * Queue is a generic MPMC queue with blocking operations
 * push() and pop().
 *
 * Two additional methods, try_push() and try_pop() allow
 * non-blocking operations.
 *
 * On a closed queue, any method will raise ClosedQueue.
 *
 * */
template <typename T, class C = std::deque<T>> class Queue {
private:
  std::queue<T, C> _queue;
  const unsigned int max_size;

  bool closed;

  std::mutex mutex;
  std::condition_variable is_not_full;
  std::condition_variable is_not_empty;

public:
  Queue() : max_size(UINT_MAX - 1), closed(false) {}
  explicit Queue(const unsigned int max_size)
      : max_size(max_size), closed(false) {}

  bool try_push(T const &val) {
    std::unique_lock<std::mutex> lock(this->mutex);

    if (this->closed) {
      throw ClosedQueue(__LINE__);
    }

    if (this->_queue.size() == this->max_size) {
      return false;
    }

    if (this->_queue.empty()) {
      this->is_not_empty.notify_all();
    }

    this->_queue.push(val);
    return true;
  }

  bool try_pop(T &val) {
    std::unique_lock<std::mutex> lock(this->mutex);

    if (this->_queue.empty()) {
      if (this->closed) {
        throw ClosedQueue(__LINE__);
      }
      return false;
    }

    if (this->_queue.size() == this->max_size) {
      this->is_not_full.notify_all();
    }

    val = this->_queue.front();
    this->_queue.pop();
    return true;
  }

  void push(T const &val) {
    std::unique_lock<std::mutex> lock(this->mutex);

    if (this->closed) {
      throw ClosedQueue(__LINE__);
    }

    while (this->_queue.size() == this->max_size) {
      this->is_not_full.wait(lock);
    }

    if (this->_queue.empty()) {
      this->is_not_empty.notify_all();
    }

    this->_queue.push(val);
  }

  T pop() {
    std::unique_lock<std::mutex> lock(this->mutex);

    while (this->_queue.empty()) {
      if (this->closed) {
        throw ClosedQueue(__LINE__);
      }
      this->is_not_empty.wait(lock);
    }

    if (this->_queue.size() == this->max_size) {
      this->is_not_full.notify_all();
    }

    T const val = this->_queue.front();
    this->_queue.pop();

    return val;
  }

  void close() {
    std::unique_lock<std::mutex> lock(this->mutex);

    if (this->closed) {
      throw std::runtime_error("The queue is already closed.");
    }

    this->closed = true;
    this->is_not_empty.notify_all();
  }

  // Queue(Queue &&);
  // Queue &operator=(Queue &&);

  // Constructor de movimiento
  Queue(Queue &&other) noexcept
      : _queue(std::move(other._queue)), max_size(other.max_size),
        closed(other.closed) {
    // Reset the state of the moved-from object
    other.closed = false;
  }

  // Operador de asignación por movimiento
  Queue &operator=(Queue &&other) noexcept {
    if (this != &other) {
      std::unique_lock<std::mutex> lock(this->mutex);
      std::unique_lock<std::mutex> other_lock(other.mutex);

      _queue = std::move(other._queue);
      // No podemos cambiar max_size ya que es const.
      closed = other.closed;
      other.closed = false;
    }
    return *this;
  }

private:
  Queue(const Queue &) = delete;
  Queue &operator=(const Queue &) = delete;
};

#endif
