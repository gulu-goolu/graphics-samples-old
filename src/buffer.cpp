//
// Created by murmur wheel on 2020/4/26.
//

#include <vkut/buffer.h>

namespace vkut {
Buffer::Buffer(VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags memory_flags) :
  size_(size),
  usage_(usage), memory_flags_(memory_flags) {
    auto device = Device::get();

    // create buffer
    VkBufferCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    create_info.size = size;
    create_info.usage = usage;
    create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.queueFamilyIndexCount = 0;
    create_info.pQueueFamilyIndices = nullptr;
    VKUT_THROW_IF_FAILED(vkCreateBuffer(
        device->vk_device(), &create_info, nullptr, &vk_buffer_));

    // allocate memory
    VkMemoryRequirements req;
    vkGetBufferMemoryRequirements(device->vk_device(), vk_buffer_, &req);

    VkMemoryAllocateInfo allocate_info = {};
    allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocate_info.memoryTypeIndex =
        device->get_memory_type(req.memoryTypeBits, memory_flags);
    allocate_info.allocationSize = req.size;
    VKUT_THROW_IF_FAILED(vkAllocateMemory(
        device->vk_device(), &allocate_info, nullptr, &vk_device_memory_));

    // bind memory
    VKUT_THROW_IF_FAILED(vkBindBufferMemory(
        device->vk_device(), vk_buffer_, vk_device_memory_, 0));
}

Buffer::~Buffer() {
    auto device = Device::get();
    if (vk_buffer_) {
        vkDestroyBuffer(device->vk_device(), vk_buffer_, nullptr);
    }
    if (vk_device_memory_) {
        vkFreeMemory(device->vk_device(), vk_device_memory_, nullptr);
    }
}
}
