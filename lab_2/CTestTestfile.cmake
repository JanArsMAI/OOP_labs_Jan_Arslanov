# CMake generated Testfile for 
# Source directory: /workspaces/oop_labs_2024/lab_2
# Build directory: /workspaces/oop_labs_2024/lab_2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyProjectTests "/workspaces/oop_labs_2024/lab_2/tests")
set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/oop_labs_2024/lab_2/CMakeLists.txt;30;add_test;/workspaces/oop_labs_2024/lab_2/CMakeLists.txt;0;")
subdirs("googletest")
