//
// Created by murmur wheel on 2020/4/26.
//

#include <vkut/pipeline.h>

namespace vkut {

PipelineLayout::~PipelineLayout() {
    if (vk_pipeline_layout_) {
        vkDestroyPipelineLayout(
            Device::get()->vk_device(), vk_pipeline_layout_, nullptr);
    }
}

ShaderModule::~ShaderModule() {
    if (vk_shader_module_) {
        vkDestroyShaderModule(
            Device::get()->vk_device(), vk_shader_module_, nullptr);
    }
}

Pipeline::Pipeline(const VkComputePipelineCreateInfo *compute_create_info) {
    auto device = Device::get();
    VKUT_THROW_IF_FAILED(vkCreateComputePipelines(device->vk_device(),
        VK_NULL_HANDLE,
        1,
        compute_create_info,
        nullptr,
        &vk_pipeline_));
}

Pipeline::Pipeline(const VkGraphicsPipelineCreateInfo *graphics_create_info) {
    auto device = Device::get();
    VKUT_THROW_IF_FAILED(vkCreateGraphicsPipelines(device->vk_device(),
        VK_NULL_HANDLE,
        1,
        graphics_create_info,
        nullptr,
        &vk_pipeline_));
}

Pipeline::~Pipeline() {
    if (vk_pipeline_) {
        auto device = Device::get();
        vkDestroyPipeline(device->vk_device(), vk_pipeline_, nullptr);
    }
}
}
