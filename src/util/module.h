//
// Created by chj on 2020/7/9.
//

#ifndef MODEL_VIEWER_MODEL_H
#define MODEL_VIEWER_MODEL_H

#include <initializer_list>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

namespace model_viewer {

class ModuleBase {
 private:
  virtual void startup() = 0;
  virtual void shutdown() = 0;

  friend class ModuleManager;
};

// 单例
class ModuleManager {
 public:
  typedef ModuleBase* (*Constructor)(void*);

  static ModuleManager* get();

  // 注册模块
  void register_module(const char* module_name, Constructor constructor,
                       size_t data_length,
                       const std::vector<std::string>& deps);
  void bind_alias(const std::string& alias, const std::string& real);
  // 启动指定的模块，若模块已经启动，直接返回
  void* startup_module(const char* module_name);
  // 启动所有模块
  void startup_all();
  // 终止所有模块
  void shutdown_all();

 private:
  struct ModuleInfo {
    ModuleBase* module_ptr_{nullptr};   // 实例
    Constructor constructor_{nullptr};  // 构造器
    size_t data_length_{0};             // 对象的长度
    std::vector<std::string> deps_;     // 依赖
  };

  std::vector<std::string> startup_order_list_;               // 启动秩序
  std::unordered_map<std::string, ModuleInfo> module_infos_;  // 模块
  std::unordered_map<std::string, std::string> alias_;        // 别名

  void prepare(const char* module_name);
};

template <typename T>
class Module : public ModuleBase {
 public:
  static T* get() {
    if (!s_module_ptr) {
      // 初始化模块
      // 调用模块的初始化函数
      s_module_ptr = reinterpret_cast<T*>(
          ModuleManager::get()->startup_module(typeid(T).name()));
    }
    return s_module_ptr;
  }

 private:
  // 模块实例的指针
  static T* s_module_ptr;
};

template <typename T>
T* Module<T>::s_module_ptr{nullptr};

}  // namespace model_viewer

// 注册模块
// 这里要注意命名空间
#define REGISTER_MODULE(NAME, ...)                                           \
  class NAME##RegisterHelper {                                               \
   public:                                                                   \
    static ::model_viewer::ModuleBase* construct(void* block) {              \
      return new (block) NAME();                                             \
    }                                                                        \
    NAME##RegisterHelper() {                                                 \
      ::model_viewer::ModuleManager::get()->register_module(                 \
          typeid(NAME).name(), construct, sizeof(NAME), __VA_ARGS__);        \
      ::model_viewer::ModuleManager::get()->bind_alias(#NAME,                \
                                                       typeid(NAME).name()); \
    }                                                                        \
  };                                                                         \
  NAME##RegisterHelper g_##NAME##_register_helper;

#endif  // MODEL_VIEWER_MODEL_H
