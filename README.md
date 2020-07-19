# graphics samples

## 内容

- 一个图形应用框架
- api 示例
- 图形 demo

## 构建

首先配置编译环境

Linux

```bash
sudo apt install libwayland-dev
```

```bash
mkdir build && cd build
cmake ..
make -j 24
```

然后在 graphics-samples/output 路径下，就是我们的输出文件
