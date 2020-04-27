//
// Created by murmur wheel on 2020/4/26.
//

#include <vkut/image.h>

namespace vkut {
ImagePtr Image::create_back_image(VkImage back_image,
    VkExtent2D extent,
    VkFormat format) {
    ImageDesc desc = {};
    desc.type = VK_IMAGE_TYPE_2D;
    desc.samples = VK_SAMPLE_COUNT_1_BIT;
    desc.extent = VkExtent3D{ extent.width, extent.height, 1 };
    desc.array_layers = 1;
    desc.mip_levels = 1;
    desc.format = format;
    desc.tiling = VK_IMAGE_TILING_OPTIMAL;
    desc.memory_flags = 0;
    return make_ptr<Image>(back_image, desc);
}

Image::Image(const ImageDesc &desc) : desc_(desc), is_back_image_(false) {}

Image::Image(VkImage vk_back_image, const ImageDesc &desc) :
  desc_(desc), is_back_image_(true), vk_image_(vk_back_image) {}

Image::~Image() {
    if (!is_back_image_) {
        auto device = Device::get();
        if (vk_image_) {
            vkDestroyImage(device->vk_device(), vk_image_, nullptr);
        }
        if (vk_device_memory_) {
            vkFreeMemory(device->vk_device(), vk_device_memory_, nullptr);
        }
    }
}

ImageView::ImageView(ImagePtr image,
    VkImageViewType view_type,
    VkFormat format,
    VkComponentMapping components,
    VkImageSubresourceRange resource_range) :
  image_ptr_(std::move(image)) {
    auto device = Device::get();

    VkImageViewCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    create_info.image = image_ptr_->vk_image();
    create_info.viewType = view_type;
    create_info.format = format;
    create_info.components = components;
    create_info.subresourceRange = resource_range;
    VKUT_THROW_IF_FAILED(vkCreateImageView(
        device->vk_device(), &create_info, nullptr, &vk_image_view_));
}

ImageView::~ImageView() {
    auto device = Device::get();
    if (vk_image_view_) {
        vkDestroyImageView(device->vk_device(), vk_image_view_, nullptr);
    }
}

}
