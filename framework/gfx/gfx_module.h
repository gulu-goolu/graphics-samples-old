//
// Created by chj on 2020/7/11.
//

#ifndef FRAMEWORK_GFX_MODULE_H
#define FRAMEWORK_GFX_MODULE_H

#include "../util/module.h"
#include "vk_api.h"

namespace framework {
class GfxModule : public TModule<GfxModule> {
 public:
  // clang-format off
  [[nodiscard]] const VkRegistryApi& registry_api() const { return registry_api_; }
  [[nodiscard]] const VkInstanceApi& instance_api() const { return instance_api_; }
  [[nodiscard]] const VkDeviceApi& device_api() const { return device_api_; }
  [[nodiscard]] const VkSurfaceKhrApi& surface_khr_api() const { return surface_khr_api_; }
  [[nodiscard]] const VkSurfaceWaylandKhrApi& surface_wayland_api() const { return surface_wayland_khr_api_; }
  [[nodiscard]] const VkSwapchainKhrApi& swapchain_khr_api() const { return swapchain_khr_api_; }
  [[nodiscard]] const VkInstance& vk_instance() const { return instance_; }
  // clang-format on

 protected:
  void startup() override;
  void shutdown() override;

  void create_instance();
  void create_device();

  // api
  void* library_{nullptr};
  VkRegistryApi registry_api_;
  VkInstanceApi instance_api_;
  VkDeviceApi device_api_;
  VkSurfaceKhrApi surface_khr_api_;
  VkSurfaceWaylandKhrApi surface_wayland_khr_api_;
  VkSwapchainKhrApi swapchain_khr_api_;

  // resources
  VkInstance instance_{nullptr};
  VkDevice device_{nullptr};
};
}  // namespace framework

#endif  // FRAMEWORK_GFX_MODULE_H
