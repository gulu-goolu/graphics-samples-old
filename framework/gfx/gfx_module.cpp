//
// Created by chj on 2020/7/11.
//

#include "gfx_module.h"

#include <dlfcn.h>

namespace framework {
void GfxModule::startup() {
  // 导入 api
  // clang-format off
  library_ = ::dlopen("libvulkan.so.1", RTLD_LAZY);
  auto vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(dlsym(library_, "vkGetInstanceProcAddr"));
  vkApi_init_RegistryApi(vkGetInstanceProcAddr, &registry_api_);
  // clang-format on

  // 创建 instance
  create_instance();
  vkApi_init_InstanceApi(instance_, registry_api_.vkGetInstanceProcAddr,
                         &instance_api_);

  // 创建 logic device
  create_device();
  vkApi_init_DeviceApi(device_, instance_api_.vkGetDeviceProcAddr,
                       &device_api_);

  // 加载 api
  vkApi_init_InstanceApi(instance_, registry_api_.vkGetInstanceProcAddr,
                         &instance_api_);
  vkApi_init_SurfaceKhrApi(instance_, registry_api_.vkGetInstanceProcAddr,
                           &surface_khr_api_);
  vkApi_init_SurfaceWaylandKhrApi(instance_api_,
                                  registry_api_.vkGetInstanceProcAddr,
                                  &surface_wayland_khr_api_);
  vkApi_init_SwapchainKhrApi(device_, instance_api_.vkGetDeviceProcAddr,
                             &swapchain_khr_api_);
}

void GfxModule::shutdown() {
  if (instance_) {
    instance_api_.vkDestroyInstance(instance_, nullptr);
  }

  // 卸载动态库
  ::dlclose(library_);
}

void GfxModule::create_instance() {
  VkApplicationInfo application_info = {};
  application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

  VkInstanceCreateInfo instance_create_info = {};
  instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

  instance_create_info.pApplicationInfo = &application_info;

  // 创建 instance 并初始化 vtbl
  VK_API_THROW_IF_FAILED(registry_api_.vkCreateInstance(&instance_create_info,
                                                        nullptr, &instance_));
  vkApi_init_InstanceApi(instance_, registry_api_.vkGetInstanceProcAddr,
                         &instance_api_);
}

void GfxModule::create_device() {
  // TODO
}

REGISTER_MODULE(GfxModule, {});
}  // namespace framework
