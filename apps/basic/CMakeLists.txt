project(basic VERSION 1.0
    DESCRIPTION "eer basic app example"
    LANGUAGES C ASM)

set(LIBS IO)
set(HAL_LIBS gpio)

include(../app.cmake)
