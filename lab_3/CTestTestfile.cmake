# CMake generated Testfile for 
# Source directory: /workspaces/oop_labs_2024/lab_3
# Build directory: /workspaces/oop_labs_2024/lab_3
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyProjectTests "/workspaces/oop_labs_2024/lab_3/tests")
set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/oop_labs_2024/lab_3/CMakeLists.txt;49;add_test;/workspaces/oop_labs_2024/lab_3/CMakeLists.txt;0;")
subdirs("googletest")
