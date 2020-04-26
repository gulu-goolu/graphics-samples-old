cmake_minimum_required(VERSION 3.10)
project(vkut)

set(VKUT_SRCS
        src/device.cpp
        src/buffer.cpp
        src/image.cpp
        src/descriptor.cpp
        src/pipeline.cpp
        src/renderpass.cpp
        src/commandbuffer.cpp src/framegraph.cpp)

add_library(vkut ${VKUT_SRCS})
target_include_directories(vkut
        PUBLIC ${PROJECT_SOURCE_DIR}/include)