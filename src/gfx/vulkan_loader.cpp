//
// Created by chj on 2020/7/9.
//

#include "vulkan_loader.h"

#include <dlfcn.h>

#include <cstdlib>

namespace model_viewer {

static VulkanLoader s_loader;

#define TO_NAME(S) #S

template <typename T>
void case_to(void* library, const char* name, T* ptr) {
  *ptr = reinterpret_cast<T>(dlsym(library, name));
}

void VulkanLoader::Startup() {
  // 加载动态库
  s_loader.library_ = dlopen("libvulkan.so.1", RTLD_LAZY);
  if (!s_loader.library_) {
    std::abort();
  }

  s_loader.bind();
}

void VulkanLoader::Shutdown() { dlclose(s_loader.library_); }

VulkanLoader* VulkanLoader::get() { return &s_loader; }

void VulkanLoader::bind() {
#define BIND(NAME) NAME = reinterpret_cast<PFN_##NAME>(dlsym(library_, #NAME))

  BIND(vkEnumerateInstanceLayerProperties);
  BIND(vkEnumerateInstanceExtensionProperties);
  BIND(vkCreateInstance);
  BIND(vkDestroyInstance);

  BIND(vkEnumeratePhysicalDevices);
  BIND(vkGetPhysicalDeviceMemoryProperties);
  BIND(vkGetPhysicalDeviceFeatures);
  BIND(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
  BIND(vkGetPhysicalDeviceSurfacePresentModesKHR);
  BIND(vkGetPhysicalDeviceFormatProperties);
  BIND(vkGetPhysicalDeviceQueueFamilyProperties);
  BIND(vkGetPhysicalDeviceImageFormatProperties);
  BIND(vkGetPhysicalDeviceProperties);
  BIND(vkGetPhysicalDeviceSurfaceFormatsKHR);

  BIND(vkCreateDevice);
}
}  // namespace model_viewer
