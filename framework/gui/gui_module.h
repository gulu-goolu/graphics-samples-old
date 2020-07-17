//
// Created by chj on 2020/7/14.
//

#ifndef MODEL_VIEWER_GUI_MODULE_H
#define MODEL_VIEWER_GUI_MODULE_H

#include "../util/module.h"

namespace model_viewer {
class GuiModule : public TModule<GuiModule> {
 public:
  void startup() override;
  void shutdown() override;
};
}  // namespace model_viewer

#endif
