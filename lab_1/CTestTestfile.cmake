# CMake generated Testfile for 
# Source directory: /workspaces/lab_1
# Build directory: /workspaces/lab_1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyProjectTests "/workspaces/lab_1/tests")
set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/lab_1/CMakeLists.txt;31;add_test;/workspaces/lab_1/CMakeLists.txt;0;")
subdirs("googletest")
