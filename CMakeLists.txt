## ----------------------------------------------------------------------------------- ##
##                                                                                     ##
## EPITECH PROJECT - Thu, Jan, 2026                                                    ##
## Title           - NanoTekSpice                                                      ##
## Description     -                                                                   ##
##     CMakeLists.txt                                                                  ##
##                                                                                     ##
## ----------------------------------------------------------------------------------- ##
##                                                                                     ##
##       _|_|_|_|  _|_|_|    _|_|_|  _|_|_|_|_|  _|_|_|_|    _|_|_|  _|    _|          ##
##       _|        _|    _|    _|        _|      _|        _|        _|    _|          ##
##       _|_|_|    _|_|_|      _|        _|      _|_|_|    _|        _|_|_|_|          ##
##       _|        _|          _|        _|      _|        _|        _|    _|          ##
##       _|_|_|_|  _|        _|_|_|      _|      _|_|_|_|    _|_|_|  _|    _|          ##
##                                                                                     ##
## ----------------------------------------------------------------------------------- ##

cmake_minimum_required(VERSION 3.16)
project(Arcade VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -fno-gnu-unique)

add_executable(arcade
    src/main.cpp
    src/Arcade/DLLoader.cpp
    src/Core/Core.cpp
)

# Test source files
set(TEST_SRC
    tests/test_file.cpp
)

target_include_directories(arcade PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
)

target_link_libraries(arcade PRIVATE dl)

set_target_properties(arcade PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_subdirectory(src/Graphics)
add_subdirectory(src/Games)
add_subdirectory(src/Menu)

# Create unit_tests executable (only when requested)
add_executable(unit_tests EXCLUDE_FROM_ALL ${TEST_SRC} ${SRC})
target_link_libraries(unit_tests PRIVATE ${CRITERION_LIBRARY})
add_custom_target(unit_test DEPENDS unit_tests)

# Custom target for running tests with coverage
add_custom_target(tests_run
    COMMAND ./unit_tests --verbose
    COMMAND gcovr --root ${CMAKE_SOURCE_DIR} --object-directory ${CMAKE_BINARY_DIR} --gcov-executable "llvm-cov gcov" --exclude tests/
    DEPENDS unit_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running unit tests and generating coverage report"
)

# Custom target for cleaning coverage files
add_custom_target(clean_coverage
    COMMAND ${CMAKE_COMMAND} -E remove -f *.gcda *.gcno *.gcov
    COMMAND ${CMAKE_COMMAND} -E remove -f tests/*.gcda tests/*.gcno tests/*.gcov
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Cleaning coverage files"
)

# Enable testing
enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)