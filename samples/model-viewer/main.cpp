//
// Created by chj on 2020/7/19.
//

#include <gflags/gflags.h>
#include <gfx/gfx_buffer.h>
#include <gfx/gfx_module.h>

#include <cstdio>
#include <memory>

namespace fw = ::framework;

int main(int argc, char* argv[]) {
  ::gflags::ParseCommandLineFlags(&argc, &argv, true);

  auto buffer = fw::GfxBuffer::Create(1024, VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  buffer.reset();

  fw::ModuleManager::Get()->shutdown_all();
}
