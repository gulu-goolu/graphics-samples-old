//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_PIPELINE_H
#define VKUT_PIPELINE_H

#include "device.h"

namespace vkut {
class PipelineLayout;
class Pipeline;
using PipelinePtr = Ptr<Pipeline>;
using PipelineLayoutPtr = Ptr<PipelineLayout>;

class PipelineLayout : public DeviceResource {
public:
    ~PipelineLayout() override;
    [[nodiscard]] const VkPipelineLayout &vk_pipeline_layout() const {
        return vk_pipeline_layout_;
    }

private:
    VkPipelineLayout vk_pipeline_layout_{ VK_NULL_HANDLE };
};

class ShaderModule : public DeviceResource {
public:
    ~ShaderModule() override;
    [[nodiscard]] const VkShaderModule &vk_shader_module() const {
        return vk_shader_module_;
    }

private:
    VkShaderModule vk_shader_module_{ VK_NULL_HANDLE };
};

class Pipeline : public DeviceResource {
public:
    explicit Pipeline(const VkGraphicsPipelineCreateInfo *graphics_create_info);
    explicit Pipeline(const VkComputePipelineCreateInfo *compute_create_info);
    ~Pipeline() override;
    [[nodiscard]] const VkPipeline &vk_pipeline() const { return vk_pipeline_; }

private:
    VkPipeline vk_pipeline_{ VK_NULL_HANDLE };
};

}

#endif // VKUT_PIPELINE_H
