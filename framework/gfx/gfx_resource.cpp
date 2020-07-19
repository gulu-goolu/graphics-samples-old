//
// Created by chj on 2020/7/19.
//

#include "gfx_resource.h"

namespace framework {
GfxBuffer::GfxBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                     VkMemoryPropertyFlags memory_flags) {
  auto gfx = GfxModule::Get();
  auto& api = gfx->device_api();

  VkBufferCreateInfo buffer_create_info = {};
  buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_create_info.size = size;
  buffer_create_info.usage = usage;
  buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  buffer_create_info.queueFamilyIndexCount = 0;
  buffer_create_info.pQueueFamilyIndices = nullptr;
  VK_API_CHECK_RESULT(api.vkCreateBuffer(gfx->vk_device(), &buffer_create_info,
                                         nullptr, &vk_buffer_));

  VkMemoryRequirements mem_req = {};
  api.vkGetBufferMemoryRequirements(gfx->vk_device(), vk_buffer_, &mem_req);

  VkMemoryAllocateInfo memory_allocate_info = {};
  memory_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  memory_allocate_info.memoryTypeIndex =
      gfx->get_memory_type(mem_req.memoryTypeBits, memory_flags);
  memory_allocate_info.allocationSize = mem_req.size;
  VK_API_CHECK_RESULT(api.vkAllocateMemory(
      gfx->vk_device(), &memory_allocate_info, nullptr, &vk_device_memory_));

  VK_API_CHECK_RESULT(api.vkBindBufferMemory(gfx->vk_device(), vk_buffer_,
                                             vk_device_memory_, 0));
}

GfxBuffer::~GfxBuffer() {
  auto gfx = GfxModule::Get();
  auto& api = gfx->device_api();

  if (vk_buffer_) {
    api.vkDestroyBuffer(gfx->vk_device(), vk_buffer_, nullptr);
  }
  if (vk_device_memory_) {
    api.vkFreeMemory(gfx->vk_device(), vk_device_memory_, nullptr);
  }
}
}  // namespace framework
