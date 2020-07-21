//
// Created by chj on 2020/7/21.
//

#ifndef FRAMEWORK_DEVICE_H
#define FRAMEWORK_DEVICE_H

#include "vk_api.h"

namespace framework {

struct VkApi {
  VkRegistryApi registry_api;
  VkInstanceApi instance_api;
  VkDeviceApi device_api;
  VkSurfaceKhrApi surface_khr_api;
  VkSurfaceWaylandKhrApi wayland_khr_api;
  VkSwapchainKhrApi swapchain_khr_api;
};

class Device {
 public:
  [[nodiscard]] const VkDevice& vk_device() const { return vk_device_; }
  [[nodiscard]] const VkDeviceApi& device_api() const { return device_api_; }

 private:
  VkDevice vk_device_{VK_NULL_HANDLE};
  VkDeviceApi device_api_;
};
}  // namespace framework

#endif  // FRAMEWORK_DEVICE_H
