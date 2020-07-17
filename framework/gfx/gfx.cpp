//
// Created by chj on 2020/7/9.
//

#include "gfx.h"

#include "vulkan_loader.h"

namespace model_viewer {
bool GfxInitialize() {
  VulkanLoader::Startup();
  return true;
}

void GfxTerminate() { VulkanLoader::Shutdown(); }
}  // namespace model_viewer
