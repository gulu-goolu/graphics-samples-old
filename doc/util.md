# util

## TModule

TModule 用来帮助定义一个模块。当我们在设计一个新模块的时候，会发现它总是会依赖于一些别的模块。如果在使用模块的时候，靠程序员手动去初始化那些被依赖的模块，很容易就会出现重复初始化或者忘记初始化的情况。为了解决此类情况，TModule 就应运而生。

定义模块，并声明依赖：

```cpp
class GuiModule : public TModule<GuiModule> {
private:
  void startup();
  void shutdown();
};
// 注册模块，GuiModule 是模块名，GfxModule 和 AssetModule 是 GuiModule 依赖的模块
REGISTER_MODULE(GuiModule, GfxModule, AssetModule);
```

使用模块：

```cpp
void func() {
  // 会初始化 GuiModule 以及关联的 TModule
  auto gui = GuiModule::get();
}
```

## 应用程序

一个应用程序拥有如下能力：

```cpp
struct IApp {
  // 启动程序
  virtual void startup() = 0;
  virtual void shutdown() = 0;
  virtual bool process_events() = 0;
  virtual void draw() = 0;
};
// 只处理和用户交互有关的时间
struct IGraphicsApp {
  virtual void handle_mouse_event(const InputMouseEvent& e) = 0;
  virtual void handle_keyboard_event(const InputKeyboardEvent& e) = 0;
};
```

实例：

```cpp
class MyGraphicsApp : public IGraphicsApp {
public:
  void startup() override {}
  // ...
};

int main() {
  MyGraphicsApp app;
  return run_app(&app, "MyGraphicsApp", 640, 480);
}
```
