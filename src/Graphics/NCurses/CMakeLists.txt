file(GLOB NCURSES_SOURCES CONFIGURE_DEPENDS "*.cpp")

if (NCURSES_SOURCES)
    add_library(arcade_ncurses SHARED ${NCURSES_SOURCES})

    target_include_directories(arcade_ncurses PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
        ${CURSES_INCLUDE_DIR}
    )

    target_link_libraries(arcade_ncurses PRIVATE ${CURSES_LIBRARIES})
    target_compile_options(arcade_ncurses PRIVATE -fno-gnu-unique)

    set_target_properties(arcade_ncurses PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    )
endif ()
