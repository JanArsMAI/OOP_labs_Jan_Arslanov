# CMake generated Testfile for 
# Source directory: /workspaces/oop_labs_2024/lab_4
# Build directory: /workspaces/oop_labs_2024/lab_4
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(lab_tests "/workspaces/oop_labs_2024/lab_4/run_tests")
set_tests_properties(lab_tests PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/oop_labs_2024/lab_4/CMakeLists.txt;25;add_test;/workspaces/oop_labs_2024/lab_4/CMakeLists.txt;0;")
subdirs("googletest")
