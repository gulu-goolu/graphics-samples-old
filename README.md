# graphics samples

## 内容

- 一个图形应用框架
- api 示例
- 图形 demo

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

通过 package.sh 将应用输出为
