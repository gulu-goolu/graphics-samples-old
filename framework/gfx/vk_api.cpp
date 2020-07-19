//
// Created by chj on 2020/7/9.
//

#include "vk_api.h"

#include <dlfcn.h>

#include <cstdlib>

namespace framework {
void vkApi_init_RegistryApi(PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr,
                            VkRegistryApi* api_ptr) {
  api_ptr->vkGetInstanceProcAddr = vkGetInstanceProcAddr;
  // clang-format off
#define BIND_PROC(NAME) api_ptr->NAME = reinterpret_cast<PFN_##NAME>(vkGetInstanceProcAddr(nullptr, #NAME))
  BIND_PROC(vkCreateInstance);
  BIND_PROC(vkEnumerateInstanceLayerProperties);
  BIND_PROC(vkEnumerateInstanceExtensionProperties);
#undef BIND_PROC
  // clang-format on
}

void vkApi_init_InstanceApi(VkInstance instance,
                            PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr,
                            VkInstanceApi* api_ptr) {
  // clang-format off
#define BIND_PROC(NAME) api_ptr->NAME = reinterpret_cast<PFN_##NAME>(vkGetInstanceProcAddr(instance, #NAME))
  BIND_PROC(vkDestroyInstance);
  BIND_PROC(vkEnumeratePhysicalDevices);
  BIND_PROC(vkEnumeratePhysicalDeviceGroups);
  BIND_PROC(vkGetDeviceProcAddr);
  BIND_PROC(vkGetPhysicalDeviceMemoryProperties);
  BIND_PROC(vkGetPhysicalDeviceFeatures);
  BIND_PROC(vkGetPhysicalDeviceFormatProperties);
  BIND_PROC(vkGetPhysicalDeviceQueueFamilyProperties);
  BIND_PROC(vkGetPhysicalDeviceImageFormatProperties);
  BIND_PROC(vkGetPhysicalDeviceProperties);
  BIND_PROC(vkCreateDevice);
#undef BIND_PROC
  // clang-format on
}

void vkApi_init_DeviceApi(VkDevice device,
                          PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr,
                          VkDeviceApi* api_ptr) {
  // clang-format off
#define BIND_PROC(NAME) api_ptr->NAME = reinterpret_cast<PFN_##NAME>(vkGetDeviceProcAddr(device, #NAME))
  BIND_PROC(vkDestroyDevice);

  // command buffer
  BIND_PROC(vkBeginCommandBuffer);
  BIND_PROC(vkEndCommandBuffer);
  BIND_PROC(vkAllocateCommandBuffers);
  BIND_PROC(vkFreeCommandBuffers);
  BIND_PROC(vkResetCommandBuffer);

  // command pool
  BIND_PROC(vkCreateCommandPool);
  BIND_PROC(vkDestroyCommandPool);
  BIND_PROC(vkTrimCommandPool);
  BIND_PROC(vkResetCommandPool);

  // descriptor set layout
  BIND_PROC(vkCreateDescriptorSetLayout);
  BIND_PROC(vkDestroyDescriptorSetLayout);

  // pipeline layout
  BIND_PROC(vkCreatePipelineLayout);
  BIND_PROC(vkDestroyPipelineLayout);

  // descriptor pool
  BIND_PROC(vkCreateDescriptorPool);
  BIND_PROC(vkDestroyDescriptorPool);

  // descriptor set
  BIND_PROC(vkAllocateDescriptorSets);
  BIND_PROC(vkFreeDescriptorSets);
  BIND_PROC(vkUpdateDescriptorSets);

  // fence
  BIND_PROC(vkCreateFence);
  BIND_PROC(vkDestroyFence);
  BIND_PROC(vkWaitForFences);
  BIND_PROC(vkResetFences);

  // pipeline
  BIND_PROC(vkCreateGraphicsPipelines);
  BIND_PROC(vkCreateComputePipelines);
  BIND_PROC(vkDestroyPipeline);

  // render pass
  BIND_PROC(vkCreateRenderPass);
  BIND_PROC(vkDestroyRenderPass);

  // framebuffer
  BIND_PROC(vkCreateFramebuffer);
  BIND_PROC(vkDestroyFramebuffer);

  // memory
  BIND_PROC(vkAllocateMemory);
  BIND_PROC(vkFreeMemory);

  // buffer
  BIND_PROC(vkCreateBuffer);
  BIND_PROC(vkDestroyBuffer);
  BIND_PROC(vkBindBufferMemory);

  // image
  BIND_PROC(vkCreateImage);
  BIND_PROC(vkDestroyImage);
  BIND_PROC(vkBindImageMemory);

  // image view
  BIND_PROC(vkCreateImageView);
  BIND_PROC(vkDestroyImageView);

  // render pass
  BIND_PROC(vkCmdBeginRenderPass);
  BIND_PROC(vkCmdEndRenderPass);
  BIND_PROC(vkCmdNextSubpass);

  // render state
  BIND_PROC(vkCmdSetViewport);
  BIND_PROC(vkCmdSetScissor);
  BIND_PROC(vkCmdSetBlendConstants);
  BIND_PROC(vkCmdSetDepthBias);
  BIND_PROC(vkCmdSetDepthBounds);
  BIND_PROC(vkCmdSetLineWidth);
  BIND_PROC(vkCmdSetStencilReference);
  BIND_PROC(vkCmdSetStencilWriteMask);

  // draw
  BIND_PROC(vkCmdDraw);
  BIND_PROC(vkCmdDrawIndexed);
  BIND_PROC(vkCmdDrawIndexedIndirect);
  BIND_PROC(vkCmdDrawIndexedIndirectCount);
  BIND_PROC(vkCmdDrawIndirect);

  // copy
  BIND_PROC(vkCmdCopyBuffer);
  BIND_PROC(vkCmdCopyImage);
  BIND_PROC(vkCmdCopyBufferToImage);
  BIND_PROC(vkCmdCopyImageToBuffer);
  BIND_PROC(vkCmdBlitImage);
  BIND_PROC(vkCmdResolveImage);
  BIND_PROC(vkCmdUpdateBuffer);
#undef BIND_PROC
  // clang-format on
}

void vkApi_init_SurfaceKhrApi(VkInstance instance,
                              PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr,
                              VkSurfaceKhrApi* api_ptr) {
  // clang-format off
#define BIND_PROC(NAME) api_ptr->NAME = reinterpret_cast<PFN_##NAME>(vkGetInstanceProcAddr(instance, #NAME))
  BIND_PROC(vkGetPhysicalDeviceSurfaceSupportKHR);
  BIND_PROC(vkGetPhysicalDeviceSurfaceFormatsKHR);
  BIND_PROC(vkDestroySurfaceKHR);
  BIND_PROC(vkGetPhysicalDeviceSurfacePresentModesKHR);
  BIND_PROC(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
#undef BIND_PROC
  // clang-format on
}

void vkApi_init_SurfaceWaylandKhrApi(
    VkInstanceApi instance, PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr,
    VkSurfaceWaylandKhrApi* api_ptr) {
  // clang-format off
#define BIND_PROC(NAME) api_ptr->NAME = reinterpret_cast<PFN_##NAME>(vkGetInstanceProcAddr(instance, #NAME))
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  BIND_PROC(vkCreateSurfaceWaylandKHR);
#endif
#undef BIND_PROC
  // clang-format on
}

void vkApi_init_SwapchainKhrApi(VkDevice device,
                                PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr,
                                VkSwapchainKhrApi* api_ptr) {
  // clang-format off
#define BIND_PROC(NAME) api_ptr->NAME = reinterpret_cast<PFN_##NAME>(vkGetDeviceProcAddr(device, #NAME))
  BIND_PROC(vkCreateSwapchainKHR);
  BIND_PROC(vkDestroySwapchainKHR);
  BIND_PROC(vkGetSwapchainImagesKHR);
  BIND_PROC(vkAcquireNextImageKHR);
  BIND_PROC(vkQueuePresentKHR);
#undef BIND_PROC
  // clang-format on
}

}  // namespace framework
