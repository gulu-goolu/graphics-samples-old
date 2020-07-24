//
// Created by chj on 2020/7/21.
//

#include "util.h"

namespace framework {
void WaitGroup::add(int val) { counter_ += val; }

void WaitGroup::done() {
  counter_--;
  if (counter_ == 0) {
    cv_.notify_one();
  }
}

void WaitGroup::wait() {
  std::unique_lock<std::mutex> lck(mtx_);
  cv_.wait(lck, [this]() -> bool { return counter_ == 0; });
}

void Semaphore::wait() {
  std::unique_lock<std::mutex> lck(mtx_);
  cv_.wait(lck, [this]() -> bool { return flag_ == true; });
  flag_ = false;
}

void Semaphore::signal() {
  std::unique_lock<std::mutex> lck(mtx_);
  flag_ = true;
  cv_.notify_one();
}

float FrameProfiler::add() {
  auto tp = std::chrono::steady_clock::now().time_since_epoch().count();

  return 0;
}
}  // namespace framework
