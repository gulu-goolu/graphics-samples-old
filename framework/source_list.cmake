set(UTIL_SOURCE_LIST
        util/macros.h
        util/module.h
        util/module.cpp
        util/sync.h
        util/sync.cpp)

set(GFX_SOURCE_LIST
        gfx/vk_api.h
        gfx/vk_api.cpp
        gfx/gfx_module.h
        gfx/gfx_module.cpp
        gfx/gfx_resource.h
        gfx/gfx_resource.cpp
        gfx/gfx_command_buffer.h
        gfx/gfx_command_buffer.cpp
        gfx/gfx.h
        gfx/gfx.cpp)

set(GUI_SOURCE_LIST
        gui/gui_module.h
        gui/gui_module.cpp
        gui/gui.h
        gui/gui.cpp)

set(SOURCE_LIST
        ${UTIL_SOURCE_LIST}
        ${GFX_SOURCE_LIST}
        ${GUI_SOURCE_LIST})