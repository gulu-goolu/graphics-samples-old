//
// Created by chj on 2020/7/21.
//

#include "platform.h"

#include <cstring>
#include <unordered_map>

namespace framework {
class PlatformFactory {
 public:
  typedef IPlatform* (*PlatformConstructor)(const char* title, int width,
                                            int height);
  static PlatformFactory* Get() {
    static PlatformFactory factory;
    return &factory;
  }

  void register_platform(const char* name, PlatformConstructor constructor) {
    platform_constructors_[name] = constructor;
  }

  IPlatform* create(const char* name, const char* title, int width,
                    int height) {
    std::string target;
    if (strcmp("default", name) == 0) {
      // 随机选一个可用的 platform
      if (!platform_constructors_.empty()) {
        target = platform_constructors_.begin()->first;
      }
    }

    if (platform_constructors_.find(target) == platform_constructors_.end()) {
      return nullptr;
    }

    return platform_constructors_[target](title, width, height);
  }

 private:
  std::unordered_map<std::string, PlatformConstructor> platform_constructors_;
};

// 用于注册 Platform 的宏
#define REGISTER_PLATFORM(PLATFORM, NAME)                                      \
  class PLATFORM##RegisterHelper {                                             \
   public:                                                                     \
    static IPlatform* create(const char* title, const int width, int height) { \
      return new PLATFORM(title, width, height);                               \
    }                                                                          \
    PLATFORM##RegisterHelper() noexcept {                                      \
      PlatformFactory::Get()->register_platform(NAME, create);                 \
    }                                                                          \
  };                                                                           \
  PLATFORM##RegisterHelper g_##PLATFORM##_register_helper

// 创建 platform
IPlatform* create_platform(const char* platform, const char* title, int width,
                           int height) {
  return PlatformFactory::Get()->create(platform, title, width, height);
}

// 平台相关的代码
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
class WaylandPlatform : public IPlatform {
 public:
  explicit WaylandPlatform(const char* title, int width, int height) {
    // 创建窗口
  }
  ~WaylandPlatform() override {
    // 销毁窗口
  }
  bool process_events(IEventHandler* handler) override {
    // 处理事件
    return true;
  }

  std::vector<std::string> get_required_extensions() override {
    std::vector<std::string> extensions;
    return extensions;
  }
  VkSurfaceKHR create_surface(VkInstance instance,
                              const VkInstanceApi& api) override {
    // 加载 wayland 的 api
    VkSurfaceWaylandKhrApi wayland_khr_api;
    vkApi_init_SurfaceWaylandKhrApi(instance, api.vkGetInstanceProcAddr,
                                    &wayland_khr_api);

    // 创建 surface
    VkSurfaceKHR surface{VK_NULL_HANDLE};

    VkWaylandSurfaceCreateInfoKHR create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    create_info.display = wl_display_;
    create_info.surface = wl_surface_;
    VK_API_CHECK_RESULT(wayland_khr_api.vkCreateWaylandSurfaceKHR(
        instance, &create_info, nullptr, &surface));

    return surface;
  }

 private:
  wl_display* wl_display_{nullptr};
  wl_surface* wl_surface_{nullptr};
};
REGISTER_PLATFORM(WaylandPlatform, "wayland");
#endif

}  // namespace framework
