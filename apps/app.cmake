add_executable(${PROJECT_NAME} ${PROJECT_NAME}.c)
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

configure_file(${EER_LIB_PATH}/include/version.h.in version.h)

# TODO: calculate size
get_property(${PROJECT_NAME}_LINKED_LIBS TARGET ${PROJECT_NAME} PROPERTY LINK_INTERFACE_LIBRARIES)
add_custom_target(${PROJECT_NAME}.usage
    ${EER_LIB_PATH}/eer-nm ${PROJECT_NAME} ${${PROJECT_NAME}_LINKED_LIBS}
    DEPENDS ${PROJECT_NAME}
)

if(EXISTS "${ARCH_PATH}/build.cmake")
    include(${ARCH_PATH}/build.cmake)
endif()

