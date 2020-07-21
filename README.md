# graphics samples

## 内容

- 3rdparty 第三方库
- frameworks 基础框架，图形 API 封装，图形应用框架
- samples 图形 demo
- doc 文档

## 构建

首先配置编译环境

```bash
# linux
sudo apt install libwayland-dev
```

拉取代码

```bash
git clone -b master --depth=1 https://github.com/murmur-wheel/graphics-samples
```

```bash
mkdir build && cd build
cmake ..
make -j 24
```

在 graphics-samples/output 路径下，就是输出的目标文件

## 打包

支持 linux, windows, 和 android 平台
