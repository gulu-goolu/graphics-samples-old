//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_FRAMEGRAPH_H
#define VKUT_FRAMEGRAPH_H

#include "pipeline.h"
#include "swapchain.h"
#include <functional>
#include <initializer_list>

namespace vkut {
using FgAttachmentId = uint32_t;
class FgTaskBuilder {
public:
    // add attachment
    FgTaskBuilder &add_color_attachment(FgAttachmentId attachment);
    // input attachment
    FgTaskBuilder &add_input_attachment(FgAttachmentId attachment,
        uint32_t set,
        uint32_t binding,
        VkSampler sampler = VK_NULL_HANDLE);
    FgTaskBuilder &resolve(FgAttachmentId src_id, FgAttachmentId dst_id);
};

class FgPipelineBuilder {
public:
    void set_primitive_topology(VkPrimitiveTopology topology);
    Ptr<Pipeline> create();
};

class FgRenderPass {
public:
    // bind to swapchain
    FgAttachmentId bind_swapchain(Ptr<Swapchain> swapchain);
    FgAttachmentId create_attachment();

    void add_task(const std::function<void(FgTaskBuilder &)> &setup_func,
        const std::function<void(FgPipelineBuilder &)> &compile_func,
        const std::function<void(VkCommandBuffer)> &execute_func);
    void compile();
    void execute();

private:
    Ptr<Swapchain> swapchain_ptr_;
};
}

#endif // VKUT_FRAMEGRAPH_H
