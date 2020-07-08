# util

## Module

Module 用来帮助定义一个模块。当我们在设计一个新模块的时候，会发现它总是会依赖于一些别的模块。如果在使用模块的时候，靠程序员手动去初始化那些被依赖的模块，很容易就会出现重复初始化或者忘记初始化的情况。为了解决此类情况，Module 就应运而生。

定义模块，并声明依赖：

```cpp
class GuiModule : public Module<GuiModule> {
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
  // 会初始化 GuiModule 以及关联的 Module
  auto gui = GuiModule::get();
}
```
