//
// Created by chj on 2020/7/19.
//

#include <gflags/gflags.h>
#include <gfx/gfx.h>
#include <tbb/concurrent_unordered_map.h>

int main(int argc, char* argv[]) {
  ::gflags::ParseCommandLineFlags(&argc, &argv, true);

  tbb::concurrent_unordered_map<int, int> m;
  m[0] = 0;
}
