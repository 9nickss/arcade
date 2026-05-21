file(GLOB SDL2_SOURCES CONFIGURE_DEPENDS "*.cpp")

find_package(SDL2_ttf QUIET)
find_package(SDL2_image QUIET)

if (SDL2_SOURCES AND SDL2_ttf_FOUND AND SDL2_image_FOUND)
    add_library(arcade_sdl2 SHARED ${SDL2_SOURCES})

    target_include_directories(arcade_sdl2 PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
        ${SDL2_INCLUDE_DIRS}
    )

    target_link_libraries(arcade_sdl2 PRIVATE ${SDL2_LIBRARIES} SDL2_ttf SDL2_image)
    target_compile_options(arcade_sdl2 PRIVATE -fno-gnu-unique)

    set_target_properties(arcade_sdl2 PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    )
elseif (SDL2_SOURCES)
    message(WARNING "SDL2_ttf or SDL2_image not found, skipping SDL2 module")
endif ()
