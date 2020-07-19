set(UTIL_SOURCE_LIST
        util/module.h
        util/module.cpp)

set(GFX_SOURCE_LIST
        gfx/vulkan_loader.h
        gfx/vulkan_loader.cpp
        gfx/gfx_device.h
        gfx/gfx_device.cpp
        gfx/gfx_module.h
        gfx/gfx_module.cpp
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