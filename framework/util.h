//
// Created by chj on 2020/7/21.
//

#ifndef FRAMEWORK_UTIL_H
#define FRAMEWORK_UTIL_H

#include <atomic>
#include <condition_variable>
#include <mutex>

#define MARK_NO_COPY(CLASS)                \
  CLASS(const CLASS&) = delete;            \
  CLASS(CLASS&&) = delete;                 \
  CLASS& operator=(const CLASS&) = delete; \
  CLASS& operator=(CLASS&&) = delete;

namespace framework {
class WaitGroup {
 public:
  MARK_NO_COPY(WaitGroup)

  WaitGroup() = default;

  void add(int val);
  void done();
  void wait();

 private:
  std::atomic<int> counter_{0};
  std::mutex mtx_;
  std::condition_variable cv_;
};

class Semaphore {
 public:
  void wait();
  void signal();

  class Guard {
   public:
    MARK_NO_COPY(Guard)

    explicit Guard(Semaphore& s) : s_(s) { s_.wait(); }
    ~Guard() { s_.signal(); }

   private:
    Semaphore& s_;
  };

 private:
  std::atomic<bool> flag_{true};
  std::mutex mtx_;
  std::condition_variable cv_;
};
}  // namespace framework

#endif  // FRAMEWORK_UTIL_H
