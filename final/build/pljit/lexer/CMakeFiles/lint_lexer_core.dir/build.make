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

# Utility rule file for lint_lexer_core.

# Include the progress variables for this target.
include pljit/lexer/CMakeFiles/lint_lexer_core.dir/progress.make

pljit/lexer/CMakeFiles/lint_lexer_core:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running lint_lexer_core"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/lexer && /usr/bin/cmake -E chdir /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/pljit/lexer /usr/bin/clang-tidy-12 -quiet -p=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/lexer Lexer.cpp

lint_lexer_core: pljit/lexer/CMakeFiles/lint_lexer_core
lint_lexer_core: pljit/lexer/CMakeFiles/lint_lexer_core.dir/build.make

.PHONY : lint_lexer_core

# Rule to build all files generated by this target.
pljit/lexer/CMakeFiles/lint_lexer_core.dir/build: lint_lexer_core

.PHONY : pljit/lexer/CMakeFiles/lint_lexer_core.dir/build

pljit/lexer/CMakeFiles/lint_lexer_core.dir/clean:
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/lexer && $(CMAKE_COMMAND) -P CMakeFiles/lint_lexer_core.dir/cmake_clean.cmake
.PHONY : pljit/lexer/CMakeFiles/lint_lexer_core.dir/clean

pljit/lexer/CMakeFiles/lint_lexer_core.dir/depend:
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ana/Documents/cpp-praktikum-exercices-latest-version/final /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/pljit/lexer /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/lexer /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/pljit/lexer/CMakeFiles/lint_lexer_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pljit/lexer/CMakeFiles/lint_lexer_core.dir/depend

