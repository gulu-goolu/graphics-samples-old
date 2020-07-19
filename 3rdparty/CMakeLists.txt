add_subdirectory(glslang-8.13.3743 glslang)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw-3.3.2 glfw)