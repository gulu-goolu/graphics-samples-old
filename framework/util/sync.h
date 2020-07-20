//
// Created by chj on 2020/7/20.
//

#ifndef FRAMEWORK_SYNC_H
#define FRAMEWORK_SYNC_H

#include <atomic>
#include <condition_variable>
#include <mutex>

#include "macros.h"

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

 private:
  std::atomic<bool> flag_{true};
  std::mutex mtx_;
  std::condition_variable cv_;
};
}  // namespace framework

#endif  // FRAMEWORK_SYNC_H
