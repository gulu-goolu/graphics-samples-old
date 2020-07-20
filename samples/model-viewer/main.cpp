//
// Created by chj on 2020/7/19.
//

#include <gflags/gflags.h>
#include <gfx/gfx_module.h>
#include <gfx/gfx_resource.h>

namespace fw = ::framework;

int main(int argc, char* argv[]) {
  ::gflags::ParseCommandLineFlags(&argc, &argv, true);

  auto gfx = ::fw::GfxModule::Get();
  auto cmd = gfx->begin_command_buffer(0);
  gfx->flush_command_buffers(cmd);

  ::fw::ModuleManager::Get()->shutdown_all();
}
