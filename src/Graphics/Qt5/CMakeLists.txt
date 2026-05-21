file(GLOB QT5_SOURCES CONFIGURE_DEPENDS "*.cpp")

if (QT5_SOURCES)
    add_library(arcade_qt5 SHARED ${QT5_SOURCES})

    target_include_directories(arcade_qt5 PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
    )

    target_link_libraries(arcade_qt5 PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
    )
    target_compile_options(arcade_qt5 PRIVATE -fno-gnu-unique)

    set_target_properties(arcade_qt5 PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    )
endif()