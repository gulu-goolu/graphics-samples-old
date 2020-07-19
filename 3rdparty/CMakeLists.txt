include(FetchContent)

# 统一导出第三方库
add_library(3rdparty_stub INTERFACE)

# gflags
FetchContent_Declare(
        gflags
        URL https://github.com/gflags/gflags/archive/v2.2.2.zip
        SOURCE_DIR gflags
)
FetchContent_GetProperties(gflags)
if (NOT gflags_POPULATED)
    FetchContent_Populate(gflags)
    add_subdirectory(${gflags_SOURCE_DIR} ${gflags_BINARY_DIR})
    target_link_libraries(3rdparty_stub INTERFACE gflags::gflags)
endif ()

# Vulkan
FetchContent_Declare(
        vulkan
        URL https://github.com/KhronosGroup/Vulkan-Headers/archive/v1.2.147.zip
        SOURCE_DIR vulkan
)
FetchContent_GetProperties(vulkan)
if (NOT vulkan_POPULATED)
    FetchContent_Populate(vulkan)
    add_subdirectory(${vulkan_SOURCE_DIR} ${vulkan_BINARY_DIR})
    target_link_libraries(3rdparty_stub INTERFACE Vulkan::Headers)
endif ()

# glslang
FetchContent_Declare(
        glslang
        URL https://github.com/KhronosGroup/glslang/archive/8.13.3743.zip
        SOURCE_DIR glslang
)
FetchContent_GetProperties(glslang)
if (NOT glslang_POPULATED)
    FetchContent_Populate(glslang)
    set(ENABLE_GLSLANG_BINARIES OFF CACHE BOOL "" FORCE)
    set(ENABLE_CTEST OFF CACHE BOOL "" FORCE)
    add_subdirectory(${glslang_SOURCE_DIR} ${glslang_BINARY_DIR})
    target_link_libraries(3rdparty_stub INTERFACE glslang)
endif ()

# stb
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb
)
FetchContent_GetProperties(stb)
if (NOT stb_POPULATED)
    FetchContent_Populate(stb)
    add_library(stb ${CMAKE_CURRENT_SOURCE_DIR}/stb/stb_impl.cpp)
    target_include_directories(stb PUBLIC ${stb_SOURCE_DIR})
    target_link_libraries(3rdparty_stub INTERFACE stb)
endif ()

# glm
FetchContent_Declare(
        glm
        URL https://github.com/g-truc/glm/archive/0.9.9.8.zip
        SOURCE_DIR glm
)
FetchContent_GetProperties(glm)
if (NOT glm_POPULATED)
    FetchContent_Populate(glm)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
    target_link_libraries(3rdparty_stub INTERFACE glm)
endif ()

# tbb
FetchContent_Declare(
        tbb
        URL https://github.com/oneapi-src/oneTBB/archive/v2020.0.zip
        SOURCE_DIR tbb
)
FetchContent_GetProperties(tbb)
if (NOT tbb_POPULATED)
    FetchContent_Populate(tbb)
    include(${tbb_SOURCE_DIR}/cmake/TBBBuild.cmake)
    tbb_build(TBB_ROOT ${tbb_SOURCE_DIR} CONFIG_DIR TBB_DIR)
    find_package(TBB REQUIRED tbb)
    target_link_libraries(3rdparty_stub INTERFACE TBB::tbb)
endif ()