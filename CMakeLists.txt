cmake_minimum_required(VERSION 3.10)
project(model-viewer)

set(CMAKE_CXX_STANDARD 17)

# gflags
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/gflags-2.2.2)

# tbb
set(TBB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/oneTBB-2020.2)
include(${TBB_PATH}/cmake/TBBBuild.cmake)
tbb_build(TBB_ROOT ${TBB_PATH} CONFIG_DIR TBB_DIR MAKE_ARGS)
find_package(TBB REQUIRED tbb)

# model viewer
include(src/source_list.cmake)
foreach (item ${SOURCE_LIST})
    list(APPEND SRCS "src/${item}")
endforeach ()
add_executable(model-viewer ${SRCS})
target_link_libraries(model-viewer dl gflags::gflags TBB::tbb)
target_include_directories(model-viewer
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/Vulkan-Headers-1.2.146/include)