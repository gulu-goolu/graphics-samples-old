//
// Created by chj on 2020/7/9.
//

#ifndef MODEL_VIEWER_GFX_H
#define MODEL_VIEWER_GFX_H

namespace model_viewer {
// 模块初始化，加载 Vulkan Api，加载各种驱动
bool GfxInitialize();

// 终止模块
void GfxTerminate();
}  // namespace model_viewer

#endif  // MODEL_VIEWER_GFX_H
