//
// Created by chj on 2020/7/8.
//

#include <gflags/gflags.h>

#include "util/module.h"

using namespace model_viewer;

class Module1 : public Module<Module1> {
  void startup() override { printf("startup Module1\n"); }
  void shutdown() override { printf("shutdown Module1\n"); }
};

class Module2 : public Module<Module2> {
  void startup() override { printf("startup Module2\n"); }
  void shutdown() override { printf("shutdown Module2\n"); }
};

class Module3 : public Module<Module3> {
  void startup() override { printf("startup Module3\n"); }
  void shutdown() override { printf("shutdown Module3\n"); }
};

REGISTER_MODULE(Module1, {});
REGISTER_MODULE(Module2, {"Module1"});
REGISTER_MODULE(Module3, {"Module2", "Module1"})

int main(int argc, char *argv[]) {
  ::gflags::ParseCommandLineFlags(&argc, &argv, true);

  ModuleManager::get()->startup_all();
  ModuleManager::get()->shutdown_all();
}