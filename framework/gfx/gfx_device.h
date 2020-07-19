//
// Created by chj on 2020/7/9.
//

#ifndef MODEL_VIEWER_GFX_DEVICE_H
#define MODEL_VIEWER_GFX_DEVICE_H

#include "vk_api.h"

namespace framework::gfx {
// 全局设备
class GfxDevice {
 public:
  static GfxDevice* get();
};
}  // namespace model_viewer::gfx

#endif  // MODEL_VIEWER_GFX_DEVICE_H
