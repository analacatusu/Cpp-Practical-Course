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
CMAKE_SOURCE_DIR = /home/ana/Documents/cpp-praktikum-exercices-latest-version/final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build

# Utility rule file for lint_semantic_core.

# Include the progress variables for this target.
include pljit/semantic/CMakeFiles/lint_semantic_core.dir/progress.make

pljit/semantic/CMakeFiles/lint_semantic_core:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running lint_semantic_core"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/semantic && /usr/bin/cmake -E chdir /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/pljit/semantic /usr/bin/clang-tidy-12 -quiet -p=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/semantic SemanticAnalysis.cpp

lint_semantic_core: pljit/semantic/CMakeFiles/lint_semantic_core
lint_semantic_core: pljit/semantic/CMakeFiles/lint_semantic_core.dir/build.make

.PHONY : lint_semantic_core

# Rule to build all files generated by this target.
pljit/semantic/CMakeFiles/lint_semantic_core.dir/build: lint_semantic_core

.PHONY : pljit/semantic/CMakeFiles/lint_semantic_core.dir/build

pljit/semantic/CMakeFiles/lint_semantic_core.dir/clean:
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/semantic && $(CMAKE_COMMAND) -P CMakeFiles/lint_semantic_core.dir/cmake_clean.cmake
.PHONY : pljit/semantic/CMakeFiles/lint_semantic_core.dir/clean

pljit/semantic/CMakeFiles/lint_semantic_core.dir/depend:
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ana/Documents/cpp-praktikum-exercices-latest-version/final /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/pljit/semantic /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/semantic /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/semantic/CMakeFiles/lint_semantic_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pljit/semantic/CMakeFiles/lint_semantic_core.dir/depend

