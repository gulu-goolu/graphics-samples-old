set(UTIL_SOURCE_LIST
        util/module.h
        util/module.cpp
        )

set(APP_SOURCE_LIST
        app/app_module.h
        app/app_module.cpp)

set(GFX_SOURCE_LIST
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
        util.h
        util.cpp
        vk_api.h
        vk_api.cpp
        device.h
        device.cpp
        platform.h
        platform.cpp
        app.h
        app.cpp
        ${UTIL_SOURCE_LIST}
        ${APP_SOURCE_LIST}
        ${GFX_SOURCE_LIST}
        ${GUI_SOURCE_LIST})