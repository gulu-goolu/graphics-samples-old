include(FetchContent)

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
endif ()