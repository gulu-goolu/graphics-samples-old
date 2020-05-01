//
// Created by murmur wheel on 2020/4/27.
//

#ifndef VKUT_SWAPCHAIN_H
#define VKUT_SWAPCHAIN_H

#include "device.h"
#include "image.h"

namespace vkut {
class Swapchain;
class Surface;
using SwapchainPtr = Ptr<Swapchain>;
using SurfacePtr = Ptr<Surface>;

class Surface : public DeviceResource {
public:
#ifdef VK_USE_PLATFORM_WIN32_KHR
    explicit Surface(VkWin32SurfaceCreateInfoKHR *win32_create_info);
#endif

    ~Surface() override;

    [[nodiscard]] const VkSurfaceKHR &vk_surface() const { return vk_surface_; }

private:
    VkSurfaceKHR vk_surface_{ VK_NULL_HANDLE };
};

class Swapchain : public DeviceResource {
public:
    explicit Swapchain(SurfacePtr surface);
    ~Swapchain() override;

    [[nodiscard]] const VkSwapchainKHR &vk_swapchain() const {
        return vk_swapchain_;
    }
    [[nodiscard]] const ImagePtr &get_image(uint32_t index) const {
        return images_[index];
    }
    [[nodiscard]] const uint32_t &back_image_index() const {
        return back_image_index_;
    }

    void resize();
    void acquire();
    void present();

private:
    void compute_image_extent();
    void select_image_format();
    void select_present_mode();
    void recreate_swapchain();
    void destroy_swapchain();

    SurfacePtr surface_ptr_;
    uint32_t present_family_index_{ 0 };
    VkFence acquire_fence_{ VK_NULL_HANDLE };

    VkSwapchainKHR vk_swapchain_{ VK_NULL_HANDLE };
    VkPresentModeKHR present_mode_{ VK_PRESENT_MODE_FIFO_KHR };
    VkExtent2D image_extent_{ 0, 0 };
    VkFormat image_format_{ VK_FORMAT_UNDEFINED };
    std::vector<ImagePtr> images_;

    uint32_t back_image_index_{ 0 };
};
}

#endif // VKUT_SWAPCHAIN_H
