//
// Created by chj on 2020/7/21.
//

#include "app.h"

#include <chrono>
#include <thread>

#include "platform.h"

namespace framework {
struct FrameProfiler {
  [[nodiscard]] float fps() const { return fps_; }
  float push(uint64_t tp) { return 0.0f; }

 private:
  int32_t head_{0}, tail_{0};
  std::array<uint64_t, 64> history_{};
  float fps_ = 0.0f;
};

struct Platform {
  virtual bool poll_events() = 0;
};

class WaylandPlatform : public Platform {
  bool poll_events() override { return true; }
};

Platform* create_wayland() { return new WaylandPlatform; }

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
