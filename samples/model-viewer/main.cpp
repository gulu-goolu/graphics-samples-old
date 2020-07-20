//
// Created by chj on 2020/7/19.
//

#include <gflags/gflags.h>
#include <gfx/gfx_module.h>
#include <gfx/gfx_resource.h>
#include <util/sync.h>

#include <thread>

namespace fw = ::framework;

int main(int argc, char* argv[]) {
  ::gflags::ParseCommandLineFlags(&argc, &argv, true);

  fw::Semaphore sem;
  int val = 0;
  std::vector<std::thread> t;
  t.reserve(24);
  for (int i = 0; i < 24; ++i) {
    t.emplace_back(std::thread([&sem, &val] {
      sem.wait();
      val += 1;
      sem.signal();
    }));
  }
  for (auto& i : t) {
    i.join();
  }
  printf("val = %d\n", val);
}
