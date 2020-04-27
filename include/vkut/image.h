//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_IMAGE_H
#define VKUT_IMAGE_H

#include "device.h"

namespace vkut {
class Image;
class ImageView;
using ImagePtr = Ptr<Image>;
using ImageViewPtr = Ptr<ImageView>;

struct ImageDesc {
    VkImageType type;
    VkExtent3D extent;
    uint32_t array_layers;
    uint32_t mip_levels;
    VkFormat format;
    VkImageUsageFlags usage;
    VkSampleCountFlagBits samples;
    VkImageTiling tiling;
    VkMemoryPropertyFlags memory_flags;

    [[nodiscard]] VkExtent2D extent2d() const {
        return VkExtent2D{ extent.width, extent.height };
    }
};

class Image : public DeviceResource {
public:
    static ImagePtr create_back_image(VkImage back_image,
        VkExtent2D extent,
        VkFormat format);

    explicit Image(const ImageDesc &desc);
    explicit Image(VkImage back_image, const ImageDesc &desc);
    ~Image() override;

    [[nodiscard]] const ImageDesc &desc() const { return desc_; }
    [[nodiscard]] const VkImage &vk_image() const { return vk_image_; }

private:
    VkImage vk_image_{ VK_NULL_HANDLE };
    VkDeviceMemory vk_device_memory_{ VK_NULL_HANDLE };

    // creating arguments
    bool is_back_image_{ false };
    ImageDesc desc_{};
};

class ImageView : public DeviceResource {
public:
    explicit ImageView(ImagePtr image,
        VkImageViewType view_type,
        VkFormat format,
        VkComponentMapping components,
        VkImageSubresourceRange resource_range);
    ~ImageView() override;

    [[nodiscard]] const ImagePtr &image_ptr() const { return image_ptr_; }
    [[nodiscard]] const VkImageView &vk_image_view() const {
        return vk_image_view_;
    }

private:
    ImagePtr image_ptr_;
    VkImageView vk_image_view_{ VK_NULL_HANDLE };
};
}

#endif // VKUT_IMAGE_H
