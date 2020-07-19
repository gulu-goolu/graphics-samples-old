//
// Created by chj on 2020/7/14.
//

#include "gui_module.h"

namespace framework {
void GuiModule::startup() { printf("GuiModule::startup()\n"); }

void GuiModule::shutdown() { printf("GuiModule::shutdown()\n"); }

REGISTER_MODULE(GuiModule, {"GfxModule"});
}  // namespace model_viewer