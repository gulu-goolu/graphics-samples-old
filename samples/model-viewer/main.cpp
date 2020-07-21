//
// Created by chj on 2020/7/19.
//

#include <app.h>
#include <gflags/gflags.h>
#include <gfx/gfx_module.h>

namespace fw = ::framework;

class MyApp : public fw::IApp {
  void startup() override {}
  void shutdown() override {}
  void render(float escaped_seconds) override {
    printf("escaped_seconds = %f\n", escaped_seconds);
  }
};

int main(int argc, char* argv[]) {
  ::gflags::ParseCommandLineFlags(&argc, &argv, true);

  MyApp app;
  fw::run_app(&app, "model-viewer", 640, 480);

  ::fw::ModuleManager::Get()->shutdown_all();
}
