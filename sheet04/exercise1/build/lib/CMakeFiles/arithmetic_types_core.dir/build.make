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
include lib/CMakeFiles/arithmetic_types_core.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/arithmetic_types_core.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/arithmetic_types_core.dir/flags.make

lib/CMakeFiles/arithmetic_types_core.dir/Complex.cpp.o: lib/CMakeFiles/arithmetic_types_core.dir/flags.make
lib/CMakeFiles/arithmetic_types_core.dir/Complex.cpp.o: ../lib/Complex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Cpp-Practical-Course/sheet04/exercise1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/arithmetic_types_core.dir/Complex.cpp.o"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arithmetic_types_core.dir/Complex.cpp.o -c /home/ana/Cpp-Practical-Course/sheet04/exercise1/lib/Complex.cpp

lib/CMakeFiles/arithmetic_types_core.dir/Complex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arithmetic_types_core.dir/Complex.cpp.i"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Cpp-Practical-Course/sheet04/exercise1/lib/Complex.cpp > CMakeFiles/arithmetic_types_core.dir/Complex.cpp.i

lib/CMakeFiles/arithmetic_types_core.dir/Complex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arithmetic_types_core.dir/Complex.cpp.s"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Cpp-Practical-Course/sheet04/exercise1/lib/Complex.cpp -o CMakeFiles/arithmetic_types_core.dir/Complex.cpp.s

lib/CMakeFiles/arithmetic_types_core.dir/Rational.cpp.o: lib/CMakeFiles/arithmetic_types_core.dir/flags.make
lib/CMakeFiles/arithmetic_types_core.dir/Rational.cpp.o: ../lib/Rational.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Cpp-Practical-Course/sheet04/exercise1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/arithmetic_types_core.dir/Rational.cpp.o"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arithmetic_types_core.dir/Rational.cpp.o -c /home/ana/Cpp-Practical-Course/sheet04/exercise1/lib/Rational.cpp

lib/CMakeFiles/arithmetic_types_core.dir/Rational.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arithmetic_types_core.dir/Rational.cpp.i"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Cpp-Practical-Course/sheet04/exercise1/lib/Rational.cpp > CMakeFiles/arithmetic_types_core.dir/Rational.cpp.i

lib/CMakeFiles/arithmetic_types_core.dir/Rational.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arithmetic_types_core.dir/Rational.cpp.s"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Cpp-Practical-Course/sheet04/exercise1/lib/Rational.cpp -o CMakeFiles/arithmetic_types_core.dir/Rational.cpp.s

# Object files for target arithmetic_types_core
arithmetic_types_core_OBJECTS = \
"CMakeFiles/arithmetic_types_core.dir/Complex.cpp.o" \
"CMakeFiles/arithmetic_types_core.dir/Rational.cpp.o"

# External object files for target arithmetic_types_core
arithmetic_types_core_EXTERNAL_OBJECTS =

lib/libarithmetic_types_core.a: lib/CMakeFiles/arithmetic_types_core.dir/Complex.cpp.o
lib/libarithmetic_types_core.a: lib/CMakeFiles/arithmetic_types_core.dir/Rational.cpp.o
lib/libarithmetic_types_core.a: lib/CMakeFiles/arithmetic_types_core.dir/build.make
lib/libarithmetic_types_core.a: lib/CMakeFiles/arithmetic_types_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ana/Cpp-Practical-Course/sheet04/exercise1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libarithmetic_types_core.a"
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/arithmetic_types_core.dir/cmake_clean_target.cmake
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arithmetic_types_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/arithmetic_types_core.dir/build: lib/libarithmetic_types_core.a

.PHONY : lib/CMakeFiles/arithmetic_types_core.dir/build

lib/CMakeFiles/arithmetic_types_core.dir/clean:
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/arithmetic_types_core.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/arithmetic_types_core.dir/clean

lib/CMakeFiles/arithmetic_types_core.dir/depend:
	cd /home/ana/Cpp-Practical-Course/sheet04/exercise1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ana/Cpp-Practical-Course/sheet04/exercise1 /home/ana/Cpp-Practical-Course/sheet04/exercise1/lib /home/ana/Cpp-Practical-Course/sheet04/exercise1/build /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib /home/ana/Cpp-Practical-Course/sheet04/exercise1/build/lib/CMakeFiles/arithmetic_types_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/arithmetic_types_core.dir/depend

