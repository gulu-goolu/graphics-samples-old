//
// Created by murmur wheel on 2020/4/26.
//

#include <unordered_map>
#include <vkut/descriptor.h>

namespace vkut {
DescriptorSetAllocator::DescriptorSetAllocator(
    uint32_t set_layout_binding_count,
    const VkDescriptorSetLayoutBinding *set_layout_bindings) {
    auto device = Device::get();

    VkDescriptorSetLayoutCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    create_info.bindingCount = set_layout_binding_count;
    create_info.pBindings = set_layout_bindings;
    VKUT_THROW_IF_FAILED(vkCreateDescriptorSetLayout(
        device->vk_device(), &create_info, nullptr, &set_layout_));

    std::unordered_map<VkDescriptorType, uint32_t> m;
    for (uint32_t i = 0; i < set_layout_binding_count; ++i) {
        m[set_layout_bindings[i].descriptorType] +=
            set_layout_bindings[i].descriptorCount;
    }
    for (auto &p : m) {
        allocation_unit_.push_back(VkDescriptorPoolSize{ p.first, p.second });
    }
}

DescriptorSetAllocator::~DescriptorSetAllocator() {
    auto device = Device::get();
    if (set_layout_) {
        vkDestroyDescriptorSetLayout(device->vk_device(), set_layout_, nullptr);
    }
    for (auto &p : pools_) {
        vkDestroyDescriptorPool(device->vk_device(), p, nullptr);
    }
}

VkDescriptorSet DescriptorSetAllocator::allocate() {
    if (!unused_sets_.empty()) {
        auto s = unused_sets_.back();
        unused_sets_.pop_back();
        return s;
    }

    auto device = Device::get();

    if (remain_count_ == 0) {
        remain_count_ = 1U << uint32_t(pools_.size());

        auto temp = allocation_unit_;
        for (auto &t : temp) {
            t.descriptorCount *= remain_count_;
        }

        VkDescriptorPool pool = VK_NULL_HANDLE;
        VkDescriptorPoolCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        create_info.poolSizeCount = uint32_t(temp.size());
        create_info.pPoolSizes = temp.data();
        create_info.maxSets = remain_count_;
        VKUT_THROW_IF_FAILED(vkCreateDescriptorPool(
            device->vk_device(), &create_info, nullptr, &pool));

        pools_.push_back(pool);
    }

    VkDescriptorSet res = VK_NULL_HANDLE;
    VkDescriptorSetAllocateInfo allocate_info = {};
    allocate_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocate_info.descriptorSetCount = 1;
    allocate_info.descriptorPool = pools_.back();
    allocate_info.pSetLayouts = &set_layout_;
    VKUT_THROW_IF_FAILED(
        vkAllocateDescriptorSets(device->vk_device(), &allocate_info, &res));

    remain_count_--;

    return res;
}

void DescriptorSetAllocator::free(VkDescriptorSet set) {
    unused_sets_.push_back(set);
}

DescriptorSet::DescriptorSet(DescriptorSetAllocatorPtr allocator) :
  allocator_ptr_(std::move(allocator)) {
    vk_descriptor_set_ = allocator_ptr_->allocate();
}

DescriptorSet::~DescriptorSet() {
    allocator_ptr_->free(vk_descriptor_set_);
}

void DescriptorSet::write_buffer_descriptor(uint32_t binding,
    VkDescriptorType descriptor_type,
    const Ptr<Buffer> &buffer,
    VkDeviceSize offset,
    VkDeviceSize range) {
    VkDescriptorBufferInfo buffer_info = {};
    buffer_info.buffer = buffer->vk_buffer();
    buffer_info.offset = offset;
    buffer_info.range = range;

    VkWriteDescriptorSet write = {};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = vk_descriptor_set_;
    write.dstBinding = binding;
    write.dstArrayElement = 0;
    write.descriptorType = descriptor_type;
    write.descriptorCount = 1;
    write.dstArrayElement = 0;
    write.pBufferInfo = &buffer_info;
    vkUpdateDescriptorSets(Device::get()->vk_device(), 1, &write, 0, nullptr);
}

}
