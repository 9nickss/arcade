file(GLOB PACMAN_SOURCES CONFIGURE_DEPENDS "*.cpp")

if (PACMAN_SOURCES)
    add_library(arcade_pacman SHARED ${PACMAN_SOURCES})

    target_include_directories(arcade_pacman PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
    )

    target_compile_options(arcade_pacman PRIVATE -fno-gnu-unique)

    set_target_properties(arcade_pacman PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    )
endif ()
