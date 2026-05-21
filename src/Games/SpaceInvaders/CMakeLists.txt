file(GLOB SPACE_INVADERS_SOURCES CONFIGURE_DEPENDS "*.cpp")

if (SPACE_INVADERS_SOURCES)
    add_library(arcade_space_invaders SHARED ${SPACE_INVADERS_SOURCES})

    target_include_directories(arcade_space_invaders PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
    )

    target_compile_options(arcade_space_invaders PRIVATE -fno-gnu-unique)

    set_target_properties(arcade_space_invaders PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    )
endif ()
