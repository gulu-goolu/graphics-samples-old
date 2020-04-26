//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_DEVICE_H
#define VKUT_DEVICE_H

#include "utility.h"

namespace vkut {

struct DeviceData;
class Device {
public:
    static void startup_offscreen();
    static void startup_game();
    static void shutdown();
    static Device *get();

    [[nodiscard]] const VkInstance &vk_instance() const;

private:
    Device();
    ~Device();

    DeviceData *data_{ nullptr };
};
}

#endif // VKUT_DEVICE_H
