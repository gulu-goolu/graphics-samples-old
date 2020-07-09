//
// Created by chj on 2020/7/9.
//

#include "module.h"

#include <cstdio>

namespace model_viewer {

ModuleManager *ModuleManager::get() {
  static ModuleManager manager;
  return &manager;
}

void ModuleManager::register_module(const char *module_name,
                                    Constructor constructor, size_t data_length,
                                    const std::vector<std::string> &deps) {
  ModuleInfo helper;
  helper.deps_ = deps;
  helper.constructor_ = constructor;

  module_infos_[module_name] = helper;
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
  for (auto it = startup_order_list_.rbegin(); it != startup_order_list_.rend();
       ++it) {
    const auto e = module_infos_[*it];
    if (e.module_ptr_) {
      // 调用 shutdown 函数
      e.module_ptr_->shutdown();

      // 释放内存
      std::free(e.module_ptr_);
    }
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

  startup_order_list_.emplace_back(module_name);
}

}  // namespace model_viewer
