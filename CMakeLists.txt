cmake_minimum_required(VERSION 3.10)
project(model-viewer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(3rdparty)

include(src/source_list.cmake)
foreach (item ${SOURCE_LIST})
    list(APPEND SRCS "src/${item}")
endforeach ()
add_executable(model-viewer ${SRCS})
target_link_libraries(model-viewer dl gflags::gflags)