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
  // clang-format on

  [[nodiscard]] const VkInstance& vk_instance() const { return vk_instance_; }
  [[nodiscard]] const VkPhysicalDevice& vk_physical_device() const {
    return vk_physical_device_;
  }
  [[nodiscard]] const VkDevice& vk_device() const { return vk_device_; }
  [[nodiscard]] const uint32_t& graphics_queue_family_index() const {
    return graphics_queue_family_index_;
  }

  // 查找匹配的 memory type index，如果需要的 memory type 不存在，将会抛出异常
  [[nodiscard]] uint32_t get_memory_type(uint32_t type_bits,
                                         VkMemoryPropertyFlags memory_flags);

 protected:
  void startup() override;
  void shutdown() override;

  void create_instance();
  void select_physical_device();
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
  VkInstance vk_instance_{nullptr};
  VkPhysicalDevice vk_physical_device_{nullptr};
  uint32_t graphics_queue_family_index_{0};
  VkDevice vk_device_{nullptr};
};
}  // namespace framework

#endif  // FRAMEWORK_GFX_MODULE_H
