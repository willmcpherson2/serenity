file(GLOB CMD_SOURCES  CONFIGURE_DEPENDS "*.cpp")

# FIXME: These tests do not use LibTest
foreach(CMD_SRC ${CMD_SOURCES})
    get_filename_component(CMD_NAME ${CMD_SRC} NAME_WE)
    add_executable(${CMD_NAME} ${CMD_SRC})
    target_link_libraries(${CMD_NAME} LibCore)
    install(TARGETS ${CMD_NAME} RUNTIME DESTINATION usr/Tests/UserEmulator)
endforeach()
