//
// Created by chj on 2020/7/21.
//

#include "app.h"

#include <chrono>
#include <thread>

#include "platform.h"

namespace framework {

class DefaultApp : public IApp {
 public:
  void startup() override {}
  void shutdown() override {}
  void render(float escaped_seconds) override {}
};

IApp* get_app(IApp* app) {
  if (app) {
    return app;
  }

  return new DefaultApp;
}

void run_app(IApp* app, const char* title, int width, int height) {
  app = get_app(app);

  app->startup();

  IPlatform* platform = create_platform("default", title, width, height);

  while (platform->process_events(app)) {
    // TODO 统计帧数
    app->render(0.0f);
    std::this_thread::yield();
  }

  app->shutdown();
}
}  // namespace framework
