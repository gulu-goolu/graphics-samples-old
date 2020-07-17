//
// Created by chj on 2020/7/9.
//

#ifndef MODEL_VIEWER_VULKAN_LOADER_H
#define MODEL_VIEWER_VULKAN_LOADER_H

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

namespace model_viewer {

class VulkanLoader {
 public:
  static void Startup();
  static void Shutdown();
  static VulkanLoader* get();

  // clang-format off
  PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties{nullptr};
  PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties{nullptr};
  PFN_vkCreateInstance vkCreateInstance{nullptr};
  PFN_vkDestroyInstance vkDestroyInstance{nullptr};

  // physical device
  PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices{nullptr};
  PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties{nullptr};
  PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures{nullptr};
  PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR{nullptr};
  PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR{nullptr};
  PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties{nullptr};
  PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties{nullptr};
  PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties{nullptr};
  PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties{nullptr};
  PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR{nullptr};

  // device
  PFN_vkCreateDevice vkCreateDevice{nullptr};

  // core api

#ifdef VK_USE_PLATFORM_WIN32_KHR
#endif // !VK_USE_PLATFORM_WIN32_KHR

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#endif // !VK_USE_PLATFORM_WAYLAND_KHR
  // clang-format on

 private:
  void* library_ = nullptr;

  // 将 api 绑定到内存中的地址
  void bind();
};

}  // namespace model_viewer

#endif  // MODEL_VIEWER_VULKAN_LOADER_H
