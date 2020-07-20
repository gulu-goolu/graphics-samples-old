add_subdirectory(tests)

add_subdirectory(model-viewer)
target_link_libraries(model-viewer framework dl)