//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_RENDERPASS_H
#define VKUT_RENDERPASS_H

#include "device.h"
#include "image.h"

namespace vkut {
class RenderPass;
class Framebuffer;
using RenderPassPtr = Ptr<RenderPass>;
using FramebufferPtr = Ptr<Framebuffer>;

class RenderPass : public DeviceResource {
public:
    [[nodiscard]] const VkRenderPass &vk_render_pass() const {
        return vk_render_pass_;
    }
    ~RenderPass() override;

private:
    VkRenderPass vk_render_pass_{ VK_NULL_HANDLE };
};

class Framebuffer : public DeviceResource {
public:
    explicit Framebuffer(RenderPassPtr render_pass,
        uint32_t width,
        uint32_t height,
        uint32_t layers,
        uint32_t attachment_count,
        ImageViewPtr *attachments);
    ~Framebuffer() override;

    [[nodiscard]] const RenderPassPtr &render_pass_ptr() const {
        return render_pass_ptr_;
    }
    [[nodiscard]] const VkFramebuffer &vk_framebuffer() const {
        return vk_framebuffer_;
    }

private:
    RenderPassPtr render_pass_ptr_;
    VkFramebuffer vk_framebuffer_{ VK_NULL_HANDLE };

    // creation args
    std::vector<Ptr<ImageView>> attachments_;
};

}

#endif // VKUT_RENDERPASS_H
