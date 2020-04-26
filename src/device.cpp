//
// Created by murmur wheel on 2020/4/26.
//

#include <cassert>
#include <unordered_map>
#include <vector>
#include <vkut/device.h>

namespace vkut {
struct DeviceStartupParams {
    std::vector<const char *> instance_layers;
    std::vector<const char *> instance_extensions;
    std::vector<const char *> device_extensions;

    static DeviceStartupParams *get() {
        static DeviceStartupParams params;
        return &params;
    }
};

struct DeviceData {
    VkInstance vk_instance{ VK_NULL_HANDLE };
    VkPhysicalDevice vk_physical_device{ VK_NULL_HANDLE };
    VkDevice vk_device{ VK_NULL_HANDLE };

    uint32_t universal_family_index_{ 0 };

    std::unordered_map<uint32_t, VkCommandPool> transient_command_pools_;
    std::unordered_map<VkCommandBuffer, uint32_t> transient_command_buffers_;
};

Device *g_device_ptr;

void Device::startup_game() {
    assert(g_device_ptr == nullptr);
    auto params = DeviceStartupParams::get();

    // instance layers
#if defined(DEBUG) || 1
    params->instance_layers.push_back("VK_LAYER_LUNARG_standard_validation");
#endif

    // instance extension
    params->instance_extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    params->instance_extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif

    // device extensions
    params->device_extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

    g_device_ptr = new Device;
}

void Device::startup_offscreen() {
    assert(g_device_ptr == nullptr);
    auto params = DeviceStartupParams::get();

    // instance layers
#if defined(DEBUG) || 1
    params->instance_layers.push_back("VK_LAYER_LUNARG_standard_validation");
#endif

    g_device_ptr = new Device;
}

void Device::shutdown() {
    delete g_device_ptr;
    g_device_ptr = nullptr;
}

Device *Device::get() {
    assert(g_device_ptr != nullptr);
    return g_device_ptr;
}

const VkInstance &Device::vk_instance() const {
    return data_->vk_instance;
}

const VkPhysicalDevice &Device::vk_physical_device() const {
    return data_->vk_physical_device;
}

const VkDevice &Device::vk_device() const {
    return data_->vk_device;
}

VkCommandBuffer Device::begin_transient(uint32_t family) {
    if (data_->transient_command_pools_[family] == VK_NULL_HANDLE) {
        VkCommandPoolCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        create_info.queueFamilyIndex = family;
        VKUT_THROW_IF_FAILED(vkCreateCommandPool(data_->vk_device,
            &create_info,
            nullptr,
            &data_->transient_command_pools_[family]));
    }

    VkCommandBuffer command_buffer = VK_NULL_HANDLE;
    VkCommandBufferAllocateInfo allocate_info = {};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = data_->transient_command_pools_[family];
    allocate_info.commandBufferCount = 1;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    VKUT_THROW_IF_FAILED(vkAllocateCommandBuffers(
        data_->vk_device, &allocate_info, &command_buffer));

    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    VKUT_THROW_IF_FAILED(vkBeginCommandBuffer(command_buffer, &begin_info));

    return command_buffer;
}

VkCommandBuffer Device::begin_transient_universal() {
    return begin_transient(data_->universal_family_index_);
}

void Device::flush_transient(VkCommandBuffer command_buffer) {
    uint32_t family = data_->transient_command_buffers_[command_buffer];

    VKUT_THROW_IF_FAILED(vkEndCommandBuffer(command_buffer));

    VkQueue q = VK_NULL_HANDLE;
    vkGetDeviceQueue(data_->vk_device, family, 0, &q);

    VkSubmitInfo submit_info = {};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &command_buffer;
    VKUT_THROW_IF_FAILED(vkQueueSubmit(q, 1, &submit_info, VK_NULL_HANDLE));
    VKUT_THROW_IF_FAILED(vkQueueWaitIdle(q));

    vkFreeCommandBuffers(data_->vk_device,
        data_->transient_command_pools_[family],
        1,
        &command_buffer);
    data_->transient_command_buffers_.erase(command_buffer);
}

Device::Device() {
    data_ = new DeviceData;

    auto params = DeviceStartupParams::get();

    // create instance
    {
        VkInstanceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.enabledLayerCount =
            uint32_t(params->instance_layers.size());
        create_info.ppEnabledLayerNames = params->instance_layers.data();
        create_info.enabledExtensionCount =
            uint32_t(params->instance_extensions.size());
        create_info.ppEnabledExtensionNames =
            params->instance_extensions.data();
        VKUT_THROW_IF_FAILED(
            vkCreateInstance(&create_info, nullptr, &data_->vk_instance));
    }

    // select physical device
    {
        uint32_t dev_cnt = 0;
        VKUT_THROW_IF_FAILED(
            vkEnumeratePhysicalDevices(data_->vk_instance, &dev_cnt, nullptr));
        std::vector<VkPhysicalDevice> devices(dev_cnt);
        VKUT_THROW_IF_FAILED(vkEnumeratePhysicalDevices(
            data_->vk_instance, &dev_cnt, devices.data()));

        data_->vk_physical_device = devices[0];
    }

    // create logic device
    {
        uint32_t family_cnt = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(
            data_->vk_physical_device, &family_cnt, nullptr);

        const float queue_priorities[1] = { 1 };
        std::vector<VkDeviceQueueCreateInfo> queue_create_infos = {};
        for (uint32_t i = 0; i < family_cnt; ++i) {
            VkDeviceQueueCreateInfo queue_info = {};
            queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_info.queueFamilyIndex = i;
            queue_info.queueCount = 1;
            queue_info.pQueuePriorities = queue_priorities;
            queue_create_infos.push_back(queue_info);
        }

        VkDeviceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount = uint32_t(queue_create_infos.size());
        create_info.pQueueCreateInfos = queue_create_infos.data();
        create_info.enabledExtensionCount =
            uint32_t(params->device_extensions.size());
        create_info.ppEnabledExtensionNames = params->device_extensions.data();
        VKUT_THROW_IF_FAILED(vkCreateDevice(data_->vk_physical_device,
            &create_info,
            nullptr,
            &data_->vk_device));
    }
}

Device::~Device() {
    for (auto &pool : data_->transient_command_pools_) {
        vkDestroyCommandPool(data_->vk_device, pool.second, nullptr);
    }
    if (data_->vk_device) {
        vkDestroyDevice(data_->vk_device, nullptr);
    }
    if (data_->vk_instance) {
        vkDestroyInstance(data_->vk_instance, nullptr);
    }
    delete data_;
}

}
