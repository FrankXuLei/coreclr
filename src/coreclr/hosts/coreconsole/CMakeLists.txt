project(CoreConsole)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
set(CoreConsole_SOURCES coreconsole.cpp logger.cpp)
set(CoreConsole_RESOURCES native.rc)

add_definitions(-DFX_VER_INTERNALNAME_STR=CoreConsole.exe)

if(CLR_CMAKE_PLATFORM_UNIX)
    # This does not compile on Linux yet
    if(CAN_BE_COMPILED_ON_LINUX)
        add_executable(CoreConsole
          ${CoreConsole_SOURCES}
          ${CoreConsole_RESOURCES}
        )
    endif(CAN_BE_COMPILED_ON_LINUX)

else()
    add_executable(CoreConsole
      ${CoreConsole_SOURCES}
      ${CoreConsole_RESOURCES}
    )

    target_link_libraries(CoreConsole
        msvcrt.lib
    )

    # Can't compile on linux yet so only add for windows
    # add the install targets
    install (TARGETS CoreConsole DESTINATION .)
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/$ENV{__BuildType}/CoreConsole.pdb DESTINATION PDB)

endif(CLR_CMAKE_PLATFORM_UNIX)