cmake_minimum_required(VERSION 3.10)
project(model-viewer)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)

# gflags
add_subdirectory(3rdparty)
add_subdirectory(framework)
add_subdirectory(samples)