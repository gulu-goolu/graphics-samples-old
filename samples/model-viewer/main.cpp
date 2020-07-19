//
// Created by chj on 2020/7/19.
//

#include <gfx/gfx_module.h>

#include <cstdio>

namespace fw = ::framework;

int main() {
  printf("hello, model-viewer\n");

  auto gfx_mdl = fw::GfxModule::Get();

  fw::ModuleManager::Get()->shutdown_all();
}
