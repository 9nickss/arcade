# CMake generated Testfile for 
# Source directory: /home/yannick/projects/G-OOP-400-NCE-4-1-arcade-3
# Build directory: /home/yannick/projects/G-OOP-400-NCE-4-1-arcade-3
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTests "/home/yannick/projects/G-OOP-400-NCE-4-1-arcade-3/unit_tests")
set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/yannick/projects/G-OOP-400-NCE-4-1-arcade-3/CMakeLists.txt;75;add_test;/home/yannick/projects/G-OOP-400-NCE-4-1-arcade-3/CMakeLists.txt;0;")
subdirs("src/Graphics")
subdirs("src/Games")
subdirs("src/Menu")
