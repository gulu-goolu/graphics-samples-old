include(source_list.cmake)
add_library(framework ${SOURCE_LIST})
target_link_libraries(framework gflags::gflags Vulkan::Headers stb)
target_include_directories(framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})