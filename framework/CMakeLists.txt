include(source_list.cmake)
add_library(framework ${SOURCE_LIST})
target_link_libraries(framework 3rdparty_stub)
target_include_directories(framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 根据平台类型，设置预编译宏 
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # linux platform
    if ($ENV{XDG_SESSION_TYPE} STREQUAL "x11")
        target_compile_definitions(framework PRIVATE -DVK_USE_PLATFORM_X11_KHR)
    else ()
        message(FATAL_MESSAGE "unsupported linux platform")
    endif ()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_compile_definitions(framework PRIVATE -DVK_USE_PLATFORM_WIN32_KHR)
else ()
    message(FATAL_ERROR "unknown platform")
endif ()
