//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_COMMANDBUFFER_H
#define VKUT_COMMANDBUFFER_H

#include "buffer.h"
#include "device.h"
#include "pipeline.h"
#include "renderpass.h"

namespace vkut {
class CommandBuffer {
public:
    explicit CommandBuffer(VkCommandBuffer command_buffer);

    [[nodiscard]] const VkCommandBuffer &vk_command_buffer() const {
        return vk_command_buffer_;
    }

    void begin();
    void end();

    void set_viewports(uint32_t first_viewport,
        uint32_t viewport_count,
        const VkViewport *viewports);
    // set first viewport
    void set_viewport(float x,
        float y,
        float width,
        float height,
        float min_depth,
        float max_depth);
    void set_scissors(uint32_t first_scissor,
        uint32_t scissor_count,
        const VkRect2D *scissors);
    // set first scissor
    void set_scissor(int32_t x, int32_t y, uint32_t width, uint32_t height);

    void begin_render_pass(const FramebufferPtr &framebuffer,
        VkRect2D render_area,
        uint32_t clear_value_count,
        const VkClearValue *clear_values,
        VkSubpassContents contents);
    void end_render_pass();
    void next_subpass(VkSubpassContents contents);

    void bind_pipeline(VkPipelineBindPoint bind_point,
        const PipelinePtr &pipeline);
    void bind_descriptor_sets();
    void bind_descriptor_set();

    void draw();
    void draw_indexed();

    void copy_buffer();
    void copy_image_to_buffer();
    void copy_buffer_to_image();
    void update_buffer(const Ptr<Buffer> &buffer,
        VkDeviceSize offset,
        VkDeviceSize size,
        const void *data);

    void image_barrier();
    void buffer_barrier();
    void pipeline_barrier(VkPipelineStageFlags src_stages,
        VkPipelineStageFlags dst_stages,
        VkDependencyFlags dependency_flags,
        uint32_t memory_barrier_count,
        const VkMemoryBarrier *memory_barriers,
        uint32_t buffer_memory_barrier_count,
        const VkBufferMemoryBarrier *buffer_memory_barriers,
        uint32_t image_memory_barrier_count,
        const VkImageMemoryBarrier *image_memory_barriers);

    void execute();

private:
    VkCommandBuffer vk_command_buffer_{ VK_NULL_HANDLE };
    std::vector<DeviceResourcePtr> related_resources_;
};
}

#endif // VKUT_COMMANDBUFFER_H
