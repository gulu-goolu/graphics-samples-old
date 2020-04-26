cmake_minimum_required(VERSION 3.10)
project(vkut)

set(VKUT_SRCS
        src/utility.cpp
        src/device.cpp
        src/buffer.cpp
        src/image.cpp
        src/descriptor.cpp
        src/pipeline.cpp
        src/renderpass.cpp
        src/commandbuffer.cpp
        src/swapchain.cpp
        src/framegraph.cpp)

add_library(vkut ${VKUT_SRCS})
target_include_directories(vkut
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

# windows platform settings
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_include_directories(vkut PUBLIC $ENV{VK_SDK_PATH}/Include)
    target_link_directories(vkut PUBLIC $ENV{VK_SDK_PATH}/Lib)
    target_compile_definitions(vkut PRIVATE -DVK_USE_PLATFORM_WIN32_KHR)
    target_link_libraries(vkut vulkan-1)
endif ()
