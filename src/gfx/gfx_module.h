//
// Created by chj on 2020/7/11.
//

#ifndef MODEL_VIEWER_GFX_MODULE_H
#define MODEL_VIEWER_GFX_MODULE_H

#include "../util/module.h"

namespace model_viewer {
class GfxModule : public TModule<GfxModule> {
 public:
  void* physical_device() { return nullptr; }
  void* device() { return nullptr; }
  void* instance() { return nullptr; }

 protected:
  void startup() override;
  void shutdown() override;
};
}  // namespace model_viewer

#endif  // MODEL_VIEWER_GFX_MODULE_H
