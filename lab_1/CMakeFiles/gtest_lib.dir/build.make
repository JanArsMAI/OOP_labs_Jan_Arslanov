# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/lab_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/lab_1

# Include any dependencies generated for this target.
include CMakeFiles/gtest_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gtest_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gtest_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gtest_lib.dir/flags.make

CMakeFiles/gtest_lib.dir/src/counter.cpp.o: CMakeFiles/gtest_lib.dir/flags.make
CMakeFiles/gtest_lib.dir/src/counter.cpp.o: src/counter.cpp
CMakeFiles/gtest_lib.dir/src/counter.cpp.o: CMakeFiles/gtest_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/lab_1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gtest_lib.dir/src/counter.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gtest_lib.dir/src/counter.cpp.o -MF CMakeFiles/gtest_lib.dir/src/counter.cpp.o.d -o CMakeFiles/gtest_lib.dir/src/counter.cpp.o -c /workspaces/lab_1/src/counter.cpp

CMakeFiles/gtest_lib.dir/src/counter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_lib.dir/src/counter.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/lab_1/src/counter.cpp > CMakeFiles/gtest_lib.dir/src/counter.cpp.i

CMakeFiles/gtest_lib.dir/src/counter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_lib.dir/src/counter.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/lab_1/src/counter.cpp -o CMakeFiles/gtest_lib.dir/src/counter.cpp.s

# Object files for target gtest_lib
gtest_lib_OBJECTS = \
"CMakeFiles/gtest_lib.dir/src/counter.cpp.o"

# External object files for target gtest_lib
gtest_lib_EXTERNAL_OBJECTS =

libgtest_lib.a: CMakeFiles/gtest_lib.dir/src/counter.cpp.o
libgtest_lib.a: CMakeFiles/gtest_lib.dir/build.make
libgtest_lib.a: CMakeFiles/gtest_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/lab_1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/gtest_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gtest_lib.dir/build: libgtest_lib.a
.PHONY : CMakeFiles/gtest_lib.dir/build

CMakeFiles/gtest_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gtest_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gtest_lib.dir/clean

CMakeFiles/gtest_lib.dir/depend:
	cd /workspaces/lab_1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/lab_1 /workspaces/lab_1 /workspaces/lab_1 /workspaces/lab_1 /workspaces/lab_1/CMakeFiles/gtest_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gtest_lib.dir/depend

