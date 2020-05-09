//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_DESCRIPTOR_H
#define VKUT_DESCRIPTOR_H

#include "buffer.h"
#include "device.h"

namespace vkut {
class DescriptorSetAllocator;
class DescriptorSet;
using DescriptorSetAllocatorPtr = Ptr<DescriptorSetAllocator>;
using DescriptorPtr = Ptr<DescriptorSet>;

class DescriptorSetAllocator final : public DeviceResource {
public:
    explicit DescriptorSetAllocator(uint32_t set_layout_binding_count,
        const VkDescriptorSetLayoutBinding *set_layout_bindings);
    ~DescriptorSetAllocator() override;

    VkDescriptorSet allocate();
    void free(VkDescriptorSet set);

private:
    VkDescriptorSetLayout set_layout_{ VK_NULL_HANDLE };
    std::vector<VkDescriptorPoolSize> allocation_unit_;
    uint32_t remain_count_{ 0 };
    std::vector<VkDescriptorPool> pools_;
    std::vector<VkDescriptorSet> unused_sets_;
};

class DescriptorSet final : public DeviceResource {
public:
    explicit DescriptorSet(DescriptorSetAllocatorPtr allocator);
    ~DescriptorSet() final;

    [[nodiscard]] const VkDescriptorSet &vk_descriptor_set() const {
        return vk_descriptor_set_;
    }

    void write_buffer_descriptor(uint32_t binding,
        VkDescriptorType descriptor_type,
        const Ptr<Buffer> &buffer,
        VkDeviceSize offset,
        VkDeviceSize range);
    void write_image_descriptor();

    static Ptr<DescriptorSet> create(DescriptorSetAllocatorPtr allocator) {
        return make_ptr<DescriptorSet>(std::move(allocator));
    }

private:
    DescriptorSetAllocatorPtr allocator_ptr_;
    VkDescriptorSet vk_descriptor_set_{ VK_NULL_HANDLE };
    std::vector<DeviceResourcePtr> related_resources_;
};
}

#endif // VKUT_DESCRIPTOR_H
