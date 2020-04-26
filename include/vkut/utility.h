//
// Created by murmur wheel on 2020/4/27.
//

#ifndef VKUT_UTILITY_H
#define VKUT_UTILITY_H

#include <vulkan/vulkan.h>

const char *vkut_cast_result_to_string(VkResult result);

#define VKUT_THROW_IF_FAILED(EXPR) \
    do { \
        VkResult r = EXPR; \
        if (r != VK_SUCCESS) { \
            throw std::exception(vkut_cast_result_to_string(r)); \
        } \
    } while (false)

#endif // VKUT_UTILITY_H
