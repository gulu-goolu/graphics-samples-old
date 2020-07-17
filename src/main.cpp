//
// Created by chj on 2020/7/8.
//

#include <gflags/gflags.h>

#include "gfx/gfx_module.h"
#include "gui/gui_module.h"
#include "util/module.h"

using namespace model_viewer;

int main(int argc, char *argv[]) {
  ::gflags::ParseCommandLineFlags(&argc, &argv, true);

  auto gfx = GfxModule::Get();
  gfx->device();

  GuiModule::Get();

  ModuleManager::Get()->shutdown_all();

  // WindowModule::Get()->get_main_window();
}