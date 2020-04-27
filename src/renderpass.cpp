//
// Created by murmur wheel on 2020/4/26.
//

#include <vkut/renderpass.h>

namespace vkut {
RenderPass::~RenderPass() {
    if (vk_render_pass_) {
        auto device = Device::get();
        vkDestroyRenderPass(device->vk_device(), vk_render_pass_, nullptr);
    }
}

Framebuffer::Framebuffer(RenderPassPtr render_pass,
    uint32_t width,
    uint32_t height,
    uint32_t layers,
    uint32_t attachment_count,
    ImageViewPtr *attachments) :
  render_pass_ptr_(std::move(render_pass)) {
    std::vector<VkImageView> views(attachment_count);
    for (uint32_t i = 0; i < attachment_count; ++i) {
        views[i] = attachments[i]->vk_image_view();
        attachments_.push_back(attachments[i]);
    }

    VkFramebufferCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    create_info.renderPass = render_pass_ptr_->vk_render_pass();
    create_info.width = width;
    create_info.height = height;
    create_info.layers = layers;
    create_info.attachmentCount = attachment_count;
    create_info.pAttachments = views.data();
    VKUT_THROW_IF_FAILED(vkCreateFramebuffer(
        Device::get()->vk_device(), &create_info, nullptr, &vk_framebuffer_));
}

Framebuffer::~Framebuffer() {
    if (vk_framebuffer_) {
        auto device = Device::get();
        vkDestroyFramebuffer(device->vk_device(), vk_framebuffer_, nullptr);
    }
}
}
