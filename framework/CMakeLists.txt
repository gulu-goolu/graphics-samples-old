
# 根据平台类型，设置预编译宏 
set(PLATFORM_LIBS "")
set(PLATFORM_MACROS "")
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # linux platform
    if ($ENV{XDG_SESSION_TYPE} STREQUAL "x11")
        list(APPEND PLATFORM_MACROS "-DVK_USE_PLATFORM_XLIB_KHR")
        list(APPEND PLATFORM_LIBS X11)
    else ()
        message(FATAL_MESSAGE "unsupported linux platform")
    endif ()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_compile_definitions(framework PRIVATE -DVK_USE_PLATFORM_WIN32_KHR)
else ()
    message(FATAL_ERROR "unknown platform")
endif ()

include(source_list.cmake)
add_library(framework ${SOURCE_LIST})
target_link_libraries(framework 3rdparty_stub ${PLATFORM_LIBS})
target_include_directories(framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(framework PUBLIC ${PLATFORM_MACROS})