//
// Created by chj on 2020/7/19.
//

#ifndef FRAMEWORK_GFX_COMMAND_BUFFER_H
#define FRAMEWORK_GFX_COMMAND_BUFFER_H

#include "gfx_module.h"
#include "gfx_resource.h"

namespace framework {
class GfxCommandBufferBuilder {
 public:
 private:
  // 关联的资源
  std::vector<std::shared_ptr<GfxResource>> related_resources_;
};
}  // namespace framework

#endif  // FRAMEWORK_GFX_COMMAND_BUFFER_H
