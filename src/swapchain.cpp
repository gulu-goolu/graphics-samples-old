//
// Created by murmur wheel on 2020/4/27.
//

#include <cassert>
#include <vkut/swapchain.h>

namespace vkut {
#ifdef VK_USE_PLATFORM_WIN32_KHR
Surface::Surface(VkWin32SurfaceCreateInfoKHR *win32_create_info) {
    VKUT_THROW_IF_FAILED(vkCreateWin32SurfaceKHR(Device::get()->vk_instance(),
        win32_create_info,
        nullptr,
        &vk_surface_));
}
#endif

Surface::~Surface() {
    if (vk_surface_) {
        vkDestroySurfaceKHR(Device::get()->vk_instance(), vk_surface_, nullptr);
    }
}

Swapchain::Swapchain(SurfacePtr surface) : surface_ptr_(std::move(surface)) {
    VkFenceCreateInfo fence_create_info = {};
    fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    VKUT_THROW_IF_FAILED(vkCreateFence(Device::get()->vk_device(),
        &fence_create_info,
        nullptr,
        &acquire_fence_));

    // get present queue family
    uint32_t family_cnt = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(
        Device::get()->vk_physical_device(), &family_cnt, nullptr);
    for (uint32_t i = 0; i < family_cnt; ++i) {
        VkBool32 supported = VK_FALSE;
        VKUT_THROW_IF_FAILED(vkGetPhysicalDeviceSurfaceSupportKHR(
            Device::get()->vk_physical_device(),
            i,
            surface_ptr_->vk_surface(),
            &supported));
        if (supported == VK_TRUE) {
            present_family_index_ = i;
            break;
        }
    }

    recreate_swapchain();
}

Swapchain::~Swapchain() {
    if (acquire_fence_) {
        vkDestroyFence(Device::get()->vk_device(), acquire_fence_, nullptr);
    }
    destroy_swapchain();
}

void Swapchain::resize() {
    destroy_swapchain();
    recreate_swapchain();
}

void Swapchain::acquire() {
    VKUT_THROW_IF_FAILED(vkAcquireNextImageKHR(Device::get()->vk_device(),
        vk_swapchain_,
        UINT64_MAX,
        VK_NULL_HANDLE,
        acquire_fence_,
        &back_image_index_));

    VKUT_THROW_IF_FAILED(vkWaitForFences(
        Device::get()->vk_device(), 1, &acquire_fence_, VK_FALSE, UINT64_MAX));
    VKUT_THROW_IF_FAILED(
        vkResetFences(Device::get()->vk_device(), 1, &acquire_fence_));
}

void Swapchain::present() {
    VkQueue queue = VK_NULL_HANDLE;
    vkGetDeviceQueue(
        Device::get()->vk_device(), present_family_index_, 0, &queue);

    VkPresentInfoKHR present_info = {};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &vk_swapchain_;
    present_info.pImageIndices = &back_image_index_;
    VKUT_THROW_IF_FAILED(vkQueuePresentKHR(queue, &present_info));
}

void Swapchain::compute_image_extent() {
    VkSurfaceCapabilitiesKHR cap = {};
    VKUT_THROW_IF_FAILED(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        Device::get()->vk_physical_device(), surface_ptr_->vk_surface(), &cap));

    image_extent_ = cap.currentExtent;
}

void Swapchain::select_image_format() {
    uint32_t fmt_cnt = 0;
    VKUT_THROW_IF_FAILED(vkGetPhysicalDeviceSurfaceFormatsKHR(
        Device::get()->vk_physical_device(),
        surface_ptr_->vk_surface(),
        &fmt_cnt,
        nullptr));

    std::vector<VkSurfaceFormatKHR> formats(fmt_cnt);
    VKUT_THROW_IF_FAILED(vkGetPhysicalDeviceSurfaceFormatsKHR(
        Device::get()->vk_physical_device(),
        surface_ptr_->vk_surface(),
        &fmt_cnt,
        formats.data()));

    std::vector<VkFormat> desired_formats = { VK_FORMAT_R8G8B8A8_UNORM };
    for (auto &f : desired_formats) {
        bool found = false;
        for (auto &s : formats) {
            if (s.format == f) {
                image_format_ = s.format;
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    assert(image_format_ != VK_FORMAT_UNDEFINED);
}

void Swapchain::select_present_mode() {
    present_mode_ = VK_PRESENT_MODE_FIFO_KHR;
}

void Swapchain::recreate_swapchain() {
    auto device = Device::get();
    // create image
    compute_image_extent();
    select_image_format();
    select_present_mode();

    VkSwapchainCreateInfoKHR create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface = surface_ptr_->vk_surface();
    create_info.minImageCount = 2;
    create_info.imageExtent = image_extent_;
    create_info.imageFormat = image_format_;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                             VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                             VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    create_info.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.presentMode = present_mode_;
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    create_info.clipped = VK_FALSE;
    create_info.queueFamilyIndexCount = 0;
    vkCreateSwapchainKHR(
        Device::get()->vk_device(), &create_info, nullptr, &vk_swapchain_);

    // retrieve images
    uint32_t image_cnt = 0;
    VKUT_THROW_IF_FAILED(vkGetSwapchainImagesKHR(
        device->vk_device(), vk_swapchain_, &image_cnt, nullptr));

    std::vector<VkImage> images(image_cnt);
    VKUT_THROW_IF_FAILED(vkGetSwapchainImagesKHR(
        device->vk_device(), vk_swapchain_, &image_cnt, images.data()));

    for (auto &img : images) {
        images_.push_back(
            Image::create_back_image(img, image_extent_, image_format_));
    }
}

void Swapchain::destroy_swapchain() {
    if (vk_swapchain_) {
        vkDestroySwapchainKHR(
            Device::get()->vk_device(), vk_swapchain_, nullptr);
    }
    images_.clear();
}

}
