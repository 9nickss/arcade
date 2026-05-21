file(GLOB MENU_SOURCES CONFIGURE_DEPENDS "*.cpp")

if (MENU_SOURCES)
    add_library(arcade_menu SHARED ${MENU_SOURCES})

    target_include_directories(arcade_menu PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
    )

    target_compile_options(arcade_menu PRIVATE -fno-gnu-unique)

    set_target_properties(arcade_menu PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    )
endif ()
