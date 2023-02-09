project(shell VERSION 1.0
    DESCRIPTION "eer shell"
    LANGUAGES C)

set(SOURCES commands.c)
set(LIBS Chip IO Clock Serial Menu)
set(HAL_LIBS gpio timer uart sys)
include(../app.cmake)
