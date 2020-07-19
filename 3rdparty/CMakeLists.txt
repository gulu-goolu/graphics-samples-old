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
