# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ana/Cpp-Practical-Course/sheet04/exercise1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ana/Cpp-Practical-Course/sheet04/exercise1/build

# Include any dependencies generated for this target.
include cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/flags.make

cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/flags.make
cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: ../cmake/thirdparty/googletest/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Cpp-Practical-Course/sheet04/exercise1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/cmake/thirdparty/googletest/googletest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/ana/Cpp-Practical-Course/sheet04/exercise1/cmake/thirdparty/googletest/googletest/src/gtest-all.cc

cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/cmake/thirdparty/googletest/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Cpp-Practical-Course/sheet04/exercise1/cmake/thirdparty/googletest/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/cmake/thirdparty/googletest/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Cpp-Practical-Course/sheet04/exercise1/cmake/thirdparty/googletest/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

lib/libgtest.a: cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
lib/libgtest.a: cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/build.make
lib/libgtest.a: cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ana/Cpp-Practical-Course/sheet04/exercise1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../../lib/libgtest.a"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/cmake/thirdparty/googletest/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/cmake/thirdparty/googletest/googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/build: lib/libgtest.a

.PHONY : cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/build

cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/clean:
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/cmake/thirdparty/googletest/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/clean

cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/depend:
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ana/Cpp-Practical-Course/sheet04/exercise1 /home/ana/Cpp-Practical-Course/sheet04/exercise1/cmake/thirdparty/googletest/googletest /home/ana/Cpp-Practical-Course/sheet04/exercise1/build /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/cmake/thirdparty/googletest/googletest /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cmake/thirdparty/googletest/googletest/CMakeFiles/gtest.dir/depend

