//
// Created by chj on 2020/7/9.
//

#include "module.h"

#include <cstdio>

namespace framework {

ModuleManager *ModuleManager::Get() {
  static ModuleManager manager;
  return &manager;
}

void ModuleManager::register_module(const char *module_name,
                                    Constructor constructor, size_t data_length,
                                    const std::vector<std::string> &deps) {
  ModuleInfo info;
  info.deps_ = deps;
  info.constructor_ = constructor;
  info.data_length_ = data_length;

  module_infos_[module_name] = info;
}

void ModuleManager::bind_alias(const std::string &alias,
                               const std::string &real) {
  alias_[alias] = real;
}

void *ModuleManager::startup_module(const char *module_name) {
  prepare(module_name);

  return module_infos_[module_name].module_ptr_;
}

void ModuleManager::startup_all() {
  for (auto &e : module_infos_) {
    prepare(e.first.c_str());
  }
}

void ModuleManager::shutdown_all() {
  // 按调用 startup 的逆序析构
  while (!startup_order_.empty()) {
    auto &e = module_infos_[startup_order_.top()];

    // 销毁模块
    e.module_ptr_->shutdown();

    // 释放内存
    std::free(e.module_ptr_);
    e.module_ptr_ = nullptr;

    startup_order_.pop();
  }
}

void ModuleManager::prepare(const char *module_name) {
  if (module_infos_[module_name].module_ptr_) {
    return;
  }

  // 解决依赖问题
  for (const auto &dep : module_infos_[module_name].deps_) {
    // 处理别名
    auto t = dep;
    if (alias_.find(dep) != alias_.end()) {
      t = alias_[dep];
    }
    //
    prepare(t.c_str());
  }

  // 构造 Module
  auto &e = module_infos_[module_name];
  e.module_ptr_ = e.constructor_(std::malloc(e.data_length_));
  e.module_ptr_->startup();

  startup_order_.push(module_name);
}

}  // namespace framework
