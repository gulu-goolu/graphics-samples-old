//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_DEVICE_H
#define VKUT_DEVICE_H

#include "utility.h"

namespace vkut {

struct DeviceData;
class Device {
public:
    static void startup_offscreen();
    static void startup_game();
    static void shutdown();
    static Device *get();

    [[nodiscard]] const VkInstance &vk_instance() const;
    [[nodiscard]] const VkPhysicalDevice &vk_physical_device() const;
    [[nodiscard]] const VkDevice &vk_device() const;

    [[nodiscard]] VkCommandBuffer begin_transient(uint32_t family);
    [[nodiscard]] VkCommandBuffer begin_transient_universal();
    void flush_transient(VkCommandBuffer command_buffer);

    [[nodiscard]] uint32_t get_memory_type(uint32_t type_bits,
        VkMemoryPropertyFlags property_flags) const;

private:
    Device();
    ~Device();

    DeviceData *data_{ nullptr };
};
}

#endif // VKUT_DEVICE_H
