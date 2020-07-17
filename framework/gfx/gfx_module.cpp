//
// Created by chj on 2020/7/11.
//

#include "gfx_module.h"

namespace model_viewer {
void GfxModule::startup() { printf("GfxModule::startup\n"); }

void GfxModule::shutdown() { printf("GfxModule::shutdown\n"); }

REGISTER_MODULE(GfxModule, {});
}  // namespace model_viewer
