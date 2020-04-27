//
// Created by murmur wheel on 2020/4/26.
//

#include <vkut/commandbuffer.h>

namespace vkut {
CommandBuffer::CommandBuffer(VkCommandBuffer command_buffer) :
  vk_command_buffer_(command_buffer) {}

void CommandBuffer::begin() {
    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    VKUT_THROW_IF_FAILED(vkBeginCommandBuffer(vk_command_buffer_, &begin_info));
}

void CommandBuffer::end() {
    VKUT_THROW_IF_FAILED(vkEndCommandBuffer(vk_command_buffer_));
}

void CommandBuffer::set_viewports(uint32_t first_viewport,
    uint32_t viewport_count,
    const VkViewport *viewports) {
    vkCmdSetViewport(
        vk_command_buffer_, first_viewport, viewport_count, viewports);
}

void CommandBuffer::set_viewport(float x,
    float y,
    float width,
    float height,
    float min_depth,
    float max_depth) {
    VkViewport vp = { x, y, width, height, min_depth, max_depth };
    vkCmdSetViewport(vk_command_buffer_, 0, 1, &vp);
}

void CommandBuffer::set_scissors(uint32_t first_scissor,
    uint32_t scissor_count,
    const VkRect2D *scissors) {
    vkCmdSetScissor(vk_command_buffer_, first_scissor, scissor_count, scissors);
}

void CommandBuffer::set_scissor(int32_t x,
    int32_t y,
    uint32_t width,
    uint32_t height) {
    VkRect2D rect = { { x, y }, { width, height } };
    vkCmdSetScissor(vk_command_buffer_, 0, 1, &rect);
}

void CommandBuffer::begin_render_pass(const FramebufferPtr &framebuffer,
    VkRect2D render_area,
    uint32_t clear_value_count,
    const VkClearValue *clear_values,
    VkSubpassContents contents) {
    VkRenderPassBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    begin_info.renderPass = framebuffer->render_pass_ptr()->vk_render_pass();
    begin_info.framebuffer = framebuffer->vk_framebuffer();
    begin_info.renderArea = render_area;
    begin_info.clearValueCount = clear_value_count;
    begin_info.pClearValues = clear_values;
    vkCmdBeginRenderPass(vk_command_buffer_, &begin_info, contents);
}

void CommandBuffer::end_render_pass() {
    vkCmdEndRenderPass(vk_command_buffer_);
}

void CommandBuffer::next_subpass(VkSubpassContents contents) {
    vkCmdNextSubpass(vk_command_buffer_, contents);
}

void CommandBuffer::bind_pipeline(VkPipelineBindPoint bind_point,
    const PipelinePtr &pipeline) {
    vkCmdBindPipeline(vk_command_buffer_, bind_point, pipeline->vk_pipeline());
}

void CommandBuffer::update_buffer(const Ptr<Buffer> &buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    const void *data) {
    vkCmdUpdateBuffer(
        vk_command_buffer_, buffer->vk_buffer(), offset, size, data);
}
}
