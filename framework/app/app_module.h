//
// Created by chj on 2020/7/20.
//

#ifndef FRAMEWORK_WINDOW_SUBSYSTEM_H
#define FRAMEWORK_WINDOW_SUBSYSTEM_H

#include <util/module.h>

namespace framework {}  // namespace framework

#define LAUNCH_APPLICATION(APP) \
  void main() {                 \
    APP app;                    \
    run_app(&app);              \
  }

#endif  // FRAMEWORK_WINDOW_MODULE_H
