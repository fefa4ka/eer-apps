project(shell VERSION 1.0
    DESCRIPTION "eer shell"
    LANGUAGES C)

set(SOURCES commands.c)
set(LIBS IO Clock Serial Menu)
set(HAL_LIBS gpio timer uart)

include(../app.cmake)
