//
// Created by chj on 2020/7/21.
//

#ifndef FRAMEWORK_APP_H
#define FRAMEWORK_APP_H

#include "platform.h"

namespace framework {
struct IApp : public IEventHandler {
  virtual void startup() = 0;
  virtual void shutdown() = 0;
  virtual void render(float escaped_seconds) = 0;
};

void run_app(IApp* app, const char* title, int width, int height);
}  // namespace framework

#endif  // FRAMEWORK_APP_H
