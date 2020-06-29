#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <vector>

namespace stout {

template <typename T>
class Notification
{
public:
  Notification() : notified_(false) {}

  void Notify(T t)
  {
    // Need to move functions to local so that we can invoke
    // them outside of mutex in the event that invoking them
    // deletes this instance and thus the mutex.
    std::vector<std::function<void(T)>> functions;

    std::call_once(
        notify_,
        [this, &t, &functions]() {
          // Copy 't' rather than 'std::move' so that we can use 't'
          // when invoking the functions in case one of the callbacks
          // deletes this instance.
          t_ = t;

          notified_.store(true, std::memory_order_release);

          mutex_.lock();
          functions = std::move(functions_);
          mutex_.unlock();
        });

    for (auto&& f : functions) {
      // See comment above for why we use 't' instead of 't_'.
      f(t);
    }
  }

  void Watch(std::function<void(T)>&& f)
  {
    if (notified_.load(std::memory_order_acquire)) {
      f(t_);
    } else {
      mutex_.lock();
      if (notified_.load(std::memory_order_acquire)) {
        mutex_.unlock();
        f(t_);
      } else {
        functions_.push_back(std::move(f));
        mutex_.unlock();
      }
    }
  }

private:
  std::mutex mutex_;
  T t_;
  std::once_flag notify_;
  std::atomic<bool> notified_;
  std::vector<std::function<void(T)>> functions_;
};

} // namespace stout {
