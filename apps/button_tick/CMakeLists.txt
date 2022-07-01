project(button_tick VERSION 1.0
    DESCRIPTION "flip gpio each interval"
    LANGUAGES C)

set(LIBS IO Button Clock)
set(HAL_LIBS gpio sys timer)

include(../app.cmake)
