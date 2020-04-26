//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_BUFFER_H
#define VKUT_BUFFER_H

#include "device.h"
#include <memory>

namespace vkut {
class Buffer;
using BufferPtr = std::shared_ptr<Buffer>;

class Buffer {
public:
    explicit Buffer(VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags memory_flags);
    ~Buffer();

    [[nodiscard]] const VkBuffer &vk_buffer() const { return vk_buffer_; }
    [[nodiscard]] const VkDeviceMemory &vk_device_memory() const {
        return vk_device_memory_;
    }

private:
    VkBuffer vk_buffer_{ VK_NULL_HANDLE };
    VkDeviceMemory vk_device_memory_{ VK_NULL_HANDLE };

    // creation arguments
    VkDeviceSize size_{ 0 };
    VkBufferUsageFlags usage_{ 0 };
    VkMemoryPropertyFlags memory_flags_{ 0 };
};

}

#endif // VKUT_BUFFER_H
