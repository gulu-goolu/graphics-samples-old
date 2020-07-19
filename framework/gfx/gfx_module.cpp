//
// Created by chj on 2020/7/11.
//

#include "gfx_module.h"

#include <dlfcn.h>
#include <gflags/gflags.h>

DEFINE_bool(enable_debug, false, "enable debug");

namespace framework {

static void get_physical_device_queue_family_properties(
    const VkInstanceApi& api, VkPhysicalDevice physical_device,
    std::vector<VkQueueFamilyProperties>& props) {
  uint32_t prop_count = 0;
  api.vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &prop_count,
                                               nullptr);

  props.resize(prop_count);
  api.vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &prop_count,
                                               props.data());
}

uint32_t GfxModule::get_memory_type(uint32_t type_bits,
                                    VkMemoryPropertyFlags memory_flags) {
  uint32_t type_index = UINT32_MAX;
  VkPhysicalDeviceMemoryProperties properties = {};
  instance_api_.vkGetPhysicalDeviceMemoryProperties(vk_physical_device_,
                                                    &properties);
  for (uint32_t i = 0; i < properties.memoryTypeCount; ++i) {
    if (type_bits & (1U << i)) {
      if ((properties.memoryTypes[i].propertyFlags & memory_flags) ==
          memory_flags) {
        type_index = i;
        break;
      }
    }
  }
  if (type_index == UINT32_MAX) {
    throw std::runtime_error("no memory type index found");
  }

  return type_index;
}

void GfxModule::startup() {
  // 导入 api
  // clang-format off
  library_ = ::dlopen("libvulkan.so.1", RTLD_LAZY);
  auto vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(dlsym(library_, "vkGetInstanceProcAddr"));
  vkApi_init_RegistryApi(vkGetInstanceProcAddr, &registry_api_);
  // clang-format on

  // 创建 instance
  create_instance();
  vkApi_init_InstanceApi(vk_instance_, registry_api_.vkGetInstanceProcAddr,
                         &instance_api_);

  // 创建 logic device
  select_physical_device();
  create_device();
  vkApi_init_DeviceApi(vk_device_, instance_api_.vkGetDeviceProcAddr,
                       &device_api_);

  // 加载 api
  vkApi_init_InstanceApi(vk_instance_, registry_api_.vkGetInstanceProcAddr,
                         &instance_api_);
  vkApi_init_SurfaceKhrApi(vk_instance_, registry_api_.vkGetInstanceProcAddr,
                           &surface_khr_api_);
  vkApi_init_SurfaceWaylandKhrApi(instance_api_,
                                  registry_api_.vkGetInstanceProcAddr,
                                  &surface_wayland_khr_api_);
  vkApi_init_SwapchainKhrApi(vk_device_, instance_api_.vkGetDeviceProcAddr,
                             &swapchain_khr_api_);
}

void GfxModule::shutdown() {
  if (vk_instance_) {
    instance_api_.vkDestroyInstance(vk_instance_, nullptr);
  }

  // 卸载动态库
  ::dlclose(library_);
}

void GfxModule::create_instance() {
  std::vector<const char*> instance_extensions;
  std::vector<const char*> instance_layers;
  if (FLAGS_enable_debug) {
  }

  VkApplicationInfo application_info = {};
  application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

  VkInstanceCreateInfo instance_create_info = {};
  instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

  instance_create_info.pApplicationInfo = &application_info;

  // 创建 instance 并初始化 vtbl
  VK_API_CHECK_RESULT(registry_api_.vkCreateInstance(&instance_create_info,
                                                     nullptr, &vk_instance_));
  vkApi_init_InstanceApi(vk_instance_, registry_api_.vkGetInstanceProcAddr,
                         &instance_api_);
}

void GfxModule::select_physical_device() {
  uint32_t physical_device_count = 0;
  VK_API_CHECK_RESULT(instance_api_.vkEnumeratePhysicalDevices(
      vk_instance_, &physical_device_count, nullptr));

  std::vector<VkPhysicalDevice> physical_devices(physical_device_count);
  VK_API_CHECK_RESULT(instance_api_.vkEnumeratePhysicalDevices(
      vk_instance_, &physical_device_count, physical_devices.data()));

  // 选择第一个支持 graphics 操作的显卡
  for (auto& physical_device : physical_devices) {
    std::vector<VkQueueFamilyProperties> props;
    get_physical_device_queue_family_properties(instance_api_, physical_device,
                                                props);

    for (uint32_t i = 0; i < props.size(); ++i) {
      const auto& prop = props[i];
      if (prop.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        graphics_queue_family_index_ = i;
        vk_physical_device_ = physical_device;
        break;
      }
    }
  }

  // 没有找到合适的图形卡
  if (!vk_physical_device_) {
    throw std::runtime_error("no graphics card found!!!");
  }
}

void GfxModule::create_device() {
  uint32_t queue_family_count = 0;
  instance_api_.vkGetPhysicalDeviceQueueFamilyProperties(
      vk_physical_device_, &queue_family_count, nullptr);

  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  const float queue_priorities[] = {1};
  for (uint32_t i = 0; i < queue_family_count; ++i) {
    VkDeviceQueueCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    create_info.queueFamilyIndex = i;
    create_info.queueCount = 1;
    create_info.pQueuePriorities = queue_priorities;

    queue_create_infos.push_back(create_info);
  }

  VkDeviceCreateInfo device_create_info = {};
  device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_create_info.queueCreateInfoCount = queue_family_count;
  device_create_info.pQueueCreateInfos = queue_create_infos.data();
  VK_API_CHECK_RESULT(instance_api_.vkCreateDevice(
      vk_physical_device_, &device_create_info, nullptr, &vk_device_));
}

REGISTER_MODULE(GfxModule, {});
}  // namespace framework
