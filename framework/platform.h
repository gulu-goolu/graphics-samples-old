//
// Created by chj on 2020/7/21.
//

#ifndef FRAMEWORK_PLATFORM_H
#define FRAMEWORK_PLATFORM_H

#include <cstdint>
#include <string>
#include <vector>

#include "vk_api.h"

namespace framework {

enum class MouseEventType {
  Undefined,
  Down,
  Up,
  Move,
};

enum class KeyboardEventType {
  Undefined,
  KeyDown,
  KeyUp,
};

enum class WindowEventType {
  Undefined,
  Resize,
  Destroy,
};

enum class InputEventType {
  Undefined,
  MouseEvent,
  KeyboardEvent,
  WindowEvent,
};

struct MouseEvent {
  MouseEventType event_type = MouseEventType::Undefined;  // 事件类型
  int x_pos{0}, y_pos{0};      // 相对于客户区的坐标
  int x_delta{0}, y_delta{0};  // 位移
};

struct KeyboardEvent {
  KeyboardEventType event_type = KeyboardEventType::Undefined;
  uint32_t key_code = 0;
};

struct WindowEvent {
  WindowEventType event_type = WindowEventType::Undefined;
  int width{0}, height{0};
};

class IEventHandler {
 public:
  virtual void handle_window_event(const WindowEvent* input_event) {}
  virtual void handle_mouse_event(const MouseEvent* input_event) {}
  virtual void handle_keyboard_event(const KeyboardEvent* input_event) {}
};

class IPlatform {
 public:
  // 返回 false, 程序结束
  virtual bool process_events(IEventHandler* event_handler) = 0;

  // surface 相关
  virtual std::vector<std::string> get_required_extensions() = 0;
  virtual VkSurfaceKHR create_surface(VkInstance instance,
                                      const VkInstanceApi& api) = 0;

  virtual ~IPlatform() = default;
};

// platform 可选的值有：default, win32, wayland, x11
IPlatform* create_platform(const char* platform, const char* title, int width,
                           int height);
}  // namespace framework

#endif  // FRAMEWORK_PLATFORM_H
