//
// Created by chj on 2020/7/21.
//

#include "app.h"

#include <chrono>
#include <thread>

#include "platform.h"

namespace framework {

void run_app(IApp* app, const char* title, int width, int height) {
  app->startup();

  IPlatform* platform = create_platform("default", title, width, height);
  // 创建 instance
  // 创建 surface

  while (platform->process_events(app)) {
    // TODO 统计帧数
    app->render(0.0f);
    std::this_thread::yield();
  }

  app->shutdown();
}
}  // namespace framework
