project(tick VERSION 1.0
    DESCRIPTION "flip gpio each interval"
    LANGUAGES C)

set(LIBS Chip IO Clock)
set(HAL_LIBS sys gpio timer)

include(../app.cmake)
