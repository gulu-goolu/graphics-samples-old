//
// Created by chj on 2020/7/9.
//

#ifndef MODEL_VIEWER_VK_API_H
#define MODEL_VIEWER_VK_API_H

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

#include <stdexcept>

namespace framework {

struct VkRegistryApi {
  // clang-format off
  PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties{nullptr};
  PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties{nullptr};
  PFN_vkCreateInstance vkCreateInstance{nullptr};
  PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr{nullptr};
  // clang-format on
};

struct VkInstanceApi {
  // clang-format off
  PFN_vkDestroyInstance vkDestroyInstance{nullptr};
  PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices{nullptr};
  PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups{nullptr};
  PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties{nullptr};
  PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures{nullptr};
  PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties{nullptr};
  PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties{nullptr};
  PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties{nullptr};
  PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties{nullptr};
  PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr{nullptr};
  PFN_vkCreateDevice vkCreateDevice{nullptr};
  // clang-format on
};

struct VkDeviceApi {
  // clang-format off
  PFN_vkDestroyDevice vkDestroyDevice{nullptr};

  // command buffer
  PFN_vkBeginCommandBuffer vkBeginCommandBuffer{nullptr};
  PFN_vkEndCommandBuffer vkEndCommandBuffer{nullptr};
  PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers{nullptr};
  PFN_vkFreeCommandBuffers vkFreeCommandBuffers{nullptr};
  PFN_vkResetCommandBuffer vkResetCommandBuffer{nullptr};

  // command pool
  PFN_vkCreateCommandPool vkCreateCommandPool{nullptr};
  PFN_vkDestroyCommandPool vkDestroyCommandPool{nullptr};
  PFN_vkTrimCommandPool vkTrimCommandPool{nullptr};
  PFN_vkResetCommandPool vkResetCommandPool{nullptr};

  // descriptor set layout
  PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout{nullptr};
  PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout{nullptr};

  // pipeline layout
  PFN_vkCreatePipelineLayout vkCreatePipelineLayout{nullptr};
  PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout{nullptr};

  // descriptor pool
  PFN_vkCreateDescriptorPool vkCreateDescriptorPool{nullptr};
  PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool{nullptr};

  // descriptor set
  PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets{nullptr};
  PFN_vkFreeDescriptorSets vkFreeDescriptorSets{nullptr};
  PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets{nullptr};

  // fence
  PFN_vkCreateFence vkCreateFence{nullptr};
  PFN_vkDestroyFence vkDestroyFence{nullptr};
  PFN_vkWaitForFences vkWaitForFences{nullptr};
  PFN_vkResetFences vkResetFences{nullptr};

  // pipeline
  PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines{nullptr};
  PFN_vkCreateComputePipelines vkCreateComputePipelines{nullptr};
  PFN_vkDestroyPipeline vkDestroyPipeline{nullptr};

  // render pass
  PFN_vkCreateRenderPass vkCreateRenderPass{nullptr};
  PFN_vkDestroyRenderPass vkDestroyRenderPass{nullptr};

  // framebuffer
  PFN_vkCreateFramebuffer vkCreateFramebuffer{nullptr};
  PFN_vkDestroyFramebuffer vkDestroyFramebuffer{nullptr};

  // memory
  PFN_vkAllocateMemory vkAllocateMemory{nullptr};
  PFN_vkFreeMemory vkFreeMemory{nullptr};

  // buffer
  PFN_vkCreateBuffer vkCreateBuffer{nullptr};
  PFN_vkDestroyBuffer vkDestroyBuffer{nullptr};
  PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements{nullptr};
  PFN_vkBindBufferMemory vkBindBufferMemory{nullptr};

  // image
  PFN_vkCreateImage vkCreateImage{nullptr};
  PFN_vkDestroyImage vkDestroyImage{nullptr};
  PFN_vkBindImageMemory vkBindImageMemory{nullptr};

  // image view
  PFN_vkCreateImageView vkCreateImageView{nullptr};
  PFN_vkDestroyImageView vkDestroyImageView{nullptr};

  // render pass
  PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass{nullptr};
  PFN_vkCmdEndRenderPass vkCmdEndRenderPass{nullptr};
  PFN_vkCmdNextSubpass vkCmdNextSubpass{nullptr};

  // render state
  PFN_vkCmdSetViewport vkCmdSetViewport{nullptr};
  PFN_vkCmdSetScissor vkCmdSetScissor{nullptr};
  PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants{nullptr};
  PFN_vkCmdSetDepthBias vkCmdSetDepthBias{nullptr};
  PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds{nullptr};
  PFN_vkCmdSetLineWidth vkCmdSetLineWidth{nullptr};
  PFN_vkCmdSetStencilReference vkCmdSetStencilReference{nullptr};
  PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask{nullptr};

  // draw
  PFN_vkCmdDraw vkCmdDraw{nullptr};
  PFN_vkCmdDrawIndexed vkCmdDrawIndexed{nullptr};
  PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect{nullptr};
  PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount{nullptr};
  PFN_vkCmdDrawIndirect vkCmdDrawIndirect{nullptr};

  // copy
  PFN_vkCmdCopyBuffer vkCmdCopyBuffer{nullptr};
  PFN_vkCmdCopyImage vkCmdCopyImage{nullptr};
  PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage{nullptr};
  PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer{nullptr};
  PFN_vkCmdBlitImage vkCmdBlitImage{nullptr};
  PFN_vkCmdResolveImage vkCmdResolveImage{nullptr};
  PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer{nullptr};

  // queue
  PFN_vkGetDeviceQueue vkGetDeviceQueue{nullptr};
  PFN_vkQueueWaitIdle vkQueueWaitIdle{nullptr};
  PFN_vkQueueSubmit vkQueueSubmit{nullptr};
  // clang-format on
};

struct VkSurfaceKhrApi {
  // clang-format off
  PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR{nullptr};
  PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR{nullptr};
  PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR{nullptr};
  PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR{nullptr};
  PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR{nullptr};
  // clang-format on
};

struct VkSurfaceWaylandKhrApi {
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  PFN_vkCreateSurfaceWaylandKHR vkCreateSurfaceWaylandKHR{nullptr};
#endif
};

struct VkSwapchainKhrApi {
  // clang-format off
  PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR{nullptr};
  PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR{nullptr};
  PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR{nullptr};
  PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR{nullptr};
  PFN_vkQueuePresentKHR vkQueuePresentKHR{nullptr};
  // clang-format on
};

void vkApi_init_RegistryApi(PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr,
                            VkRegistryApi* api_ptr);
void vkApi_init_InstanceApi(VkInstance instance,
                            PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr,
                            VkInstanceApi* api_ptr);
void vkApi_init_DeviceApi(VkDevice device,
                          PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr,
                          VkDeviceApi* api_ptr);
void vkApi_init_SurfaceKhrApi(VkInstance instance,
                              PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr,
                              VkSurfaceKhrApi* api_ptr);
void vkApi_init_SurfaceWaylandKhrApi(
    VkInstanceApi instance, PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr,
    VkSurfaceWaylandKhrApi* api_ptr);
void vkApi_init_SwapchainKhrApi(VkDevice device,
                                PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr,
                                VkSwapchainKhrApi* api_ptr);

#define VK_API_CHECK_RESULT(EXPR)         \
  do {                                    \
    VkResult result = EXPR;               \
    if (result != VK_SUCCESS) {           \
      throw std::invalid_argument(#EXPR); \
    }                                     \
  } while (false)
}  // namespace framework

#endif  // MODEL_VIEWER_VK_API_H
