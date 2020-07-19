include(source_list.cmake)
add_library(framework ${SOURCE_LIST})
target_link_libraries(framework 3rdparty_stub)
target_include_directories(framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})