//
// Created by chj on 2020/7/19.
//

#ifndef FRAMEWORK_GFX_BUFFER_H
#define FRAMEWORK_GFX_BUFFER_H

#include <memory>

#include "gfx_module.h"

namespace framework {
class GfxBuffer {
 public:
  explicit GfxBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                     VkMemoryPropertyFlags memory_flags);
  ~GfxBuffer();

  // 写入数据
  void write(VkDeviceSize offset, VkDeviceSize size, const void* buf);

  // 读取数据
  void read(VkDeviceSize offset, VkDeviceSize size, void* buf);

  void update_access_flags(VkCommandBuffer command_buffer,
                           VkAccessFlags access_flags);

  void update_access_flags(VkAccessFlags access_flags);

  // 创建一个 Buffer
  static std::shared_ptr<GfxBuffer> Create(VkDeviceSize size,
                                           VkBufferUsageFlags usage,
                                           VkMemoryPropertyFlags memory_flags) {
    return std::make_shared<GfxBuffer>(size, usage, memory_flags);
  }

 private:
  VkBuffer vk_buffer_{nullptr};
  VkDeviceMemory vk_device_memory_{nullptr};

  // 状态
  VkAccessFlags access_flags_{0};
};
}  // namespace framework

#endif  // FRAMEWORK_GFX_BUFFER_H
