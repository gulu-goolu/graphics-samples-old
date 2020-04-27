//
// Created by murmur wheel on 2020/4/27.
//

#ifndef VKUT_SWAPCHAIN_H
#define VKUT_SWAPCHAIN_H

#include "device.h"
#include "image.h"

namespace vkut {
class Swapchain;
using SwapchainPtr = std::shared_ptr<Swapchain>;

class Swapchain {
public:
#ifdef VK_USE_PLATFORM_WIN32_KHR
    static SwapchainPtr create_from_hwnd(HWND hwnd);
#endif

    explicit Swapchain(VkSurfaceKHR vk_surface);

private:
    std::vector<ImagePtr> images_;
};
}

#endif // VKUT_SWAPCHAIN_H
