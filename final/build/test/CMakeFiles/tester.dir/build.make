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

# Include any dependencies generated for this target.
include test/CMakeFiles/tester.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/tester.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/tester.dir/flags.make

test/CMakeFiles/tester.dir/TestLexer.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/TestLexer.cpp.o: ../test/TestLexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/tester.dir/TestLexer.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/TestLexer.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestLexer.cpp

test/CMakeFiles/tester.dir/TestLexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/TestLexer.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestLexer.cpp > CMakeFiles/tester.dir/TestLexer.cpp.i

test/CMakeFiles/tester.dir/TestLexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/TestLexer.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestLexer.cpp -o CMakeFiles/tester.dir/TestLexer.cpp.s

test/CMakeFiles/tester.dir/TestParser.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/TestParser.cpp.o: ../test/TestParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/tester.dir/TestParser.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/TestParser.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestParser.cpp

test/CMakeFiles/tester.dir/TestParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/TestParser.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestParser.cpp > CMakeFiles/tester.dir/TestParser.cpp.i

test/CMakeFiles/tester.dir/TestParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/TestParser.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestParser.cpp -o CMakeFiles/tester.dir/TestParser.cpp.s

test/CMakeFiles/tester.dir/TestAST.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/TestAST.cpp.o: ../test/TestAST.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/tester.dir/TestAST.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/TestAST.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestAST.cpp

test/CMakeFiles/tester.dir/TestAST.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/TestAST.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestAST.cpp > CMakeFiles/tester.dir/TestAST.cpp.i

test/CMakeFiles/tester.dir/TestAST.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/TestAST.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestAST.cpp -o CMakeFiles/tester.dir/TestAST.cpp.s

test/CMakeFiles/tester.dir/TestEvaluation.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/TestEvaluation.cpp.o: ../test/TestEvaluation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object test/CMakeFiles/tester.dir/TestEvaluation.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/TestEvaluation.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestEvaluation.cpp

test/CMakeFiles/tester.dir/TestEvaluation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/TestEvaluation.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestEvaluation.cpp > CMakeFiles/tester.dir/TestEvaluation.cpp.i

test/CMakeFiles/tester.dir/TestEvaluation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/TestEvaluation.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestEvaluation.cpp -o CMakeFiles/tester.dir/TestEvaluation.cpp.s

test/CMakeFiles/tester.dir/TestOptimization.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/TestOptimization.cpp.o: ../test/TestOptimization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object test/CMakeFiles/tester.dir/TestOptimization.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/TestOptimization.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestOptimization.cpp

test/CMakeFiles/tester.dir/TestOptimization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/TestOptimization.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestOptimization.cpp > CMakeFiles/tester.dir/TestOptimization.cpp.i

test/CMakeFiles/tester.dir/TestOptimization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/TestOptimization.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestOptimization.cpp -o CMakeFiles/tester.dir/TestOptimization.cpp.s

test/CMakeFiles/tester.dir/TestPljit.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/TestPljit.cpp.o: ../test/TestPljit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object test/CMakeFiles/tester.dir/TestPljit.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/TestPljit.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestPljit.cpp

test/CMakeFiles/tester.dir/TestPljit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/TestPljit.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestPljit.cpp > CMakeFiles/tester.dir/TestPljit.cpp.i

test/CMakeFiles/tester.dir/TestPljit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/TestPljit.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestPljit.cpp -o CMakeFiles/tester.dir/TestPljit.cpp.s

test/CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.o: ../test/TestASTPrintVisitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object test/CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestASTPrintVisitor.cpp

test/CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestASTPrintVisitor.cpp > CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.i

test/CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestASTPrintVisitor.cpp -o CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.s

test/CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.o: ../test/TestParseTreePrintVisitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object test/CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestParseTreePrintVisitor.cpp

test/CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestParseTreePrintVisitor.cpp > CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.i

test/CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/TestParseTreePrintVisitor.cpp -o CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.s

test/CMakeFiles/tester.dir/Tester.cpp.o: test/CMakeFiles/tester.dir/flags.make
test/CMakeFiles/tester.dir/Tester.cpp.o: ../test/Tester.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object test/CMakeFiles/tester.dir/Tester.cpp.o"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/Tester.cpp.o -c /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/Tester.cpp

test/CMakeFiles/tester.dir/Tester.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/Tester.cpp.i"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/Tester.cpp > CMakeFiles/tester.dir/Tester.cpp.i

test/CMakeFiles/tester.dir/Tester.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/Tester.cpp.s"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test/Tester.cpp -o CMakeFiles/tester.dir/Tester.cpp.s

# Object files for target tester
tester_OBJECTS = \
"CMakeFiles/tester.dir/TestLexer.cpp.o" \
"CMakeFiles/tester.dir/TestParser.cpp.o" \
"CMakeFiles/tester.dir/TestAST.cpp.o" \
"CMakeFiles/tester.dir/TestEvaluation.cpp.o" \
"CMakeFiles/tester.dir/TestOptimization.cpp.o" \
"CMakeFiles/tester.dir/TestPljit.cpp.o" \
"CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.o" \
"CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.o" \
"CMakeFiles/tester.dir/Tester.cpp.o"

# External object files for target tester
tester_EXTERNAL_OBJECTS =

test/tester: test/CMakeFiles/tester.dir/TestLexer.cpp.o
test/tester: test/CMakeFiles/tester.dir/TestParser.cpp.o
test/tester: test/CMakeFiles/tester.dir/TestAST.cpp.o
test/tester: test/CMakeFiles/tester.dir/TestEvaluation.cpp.o
test/tester: test/CMakeFiles/tester.dir/TestOptimization.cpp.o
test/tester: test/CMakeFiles/tester.dir/TestPljit.cpp.o
test/tester: test/CMakeFiles/tester.dir/TestASTPrintVisitor.cpp.o
test/tester: test/CMakeFiles/tester.dir/TestParseTreePrintVisitor.cpp.o
test/tester: test/CMakeFiles/tester.dir/Tester.cpp.o
test/tester: test/CMakeFiles/tester.dir/build.make
test/tester: pljit/libpljit_core.a
test/tester: lib/libgtest.a
test/tester: pljit/semantic/libsemantic_core.a
test/tester: pljit/ast/libast_core.a
test/tester: pljit/evaluation/libevaluation_core.a
test/tester: pljit/parser/libparser_core.a
test/tester: pljit/parsetree/libparsetree_core.a
test/tester: pljit/lexer/liblexer_core.a
test/tester: pljit/codem/libcodem_core.a
test/tester: test/CMakeFiles/tester.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable tester"
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tester.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/tester.dir/build: test/tester

.PHONY : test/CMakeFiles/tester.dir/build

test/CMakeFiles/tester.dir/clean:
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test && $(CMAKE_COMMAND) -P CMakeFiles/tester.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/tester.dir/clean

test/CMakeFiles/tester.dir/depend:
	cd /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ana/Documents/cpp-praktikum-exercices-latest-version/final /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/test /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test /home/ana/Documents/cpp-praktikum-exercices-latest-version/final/build/test/CMakeFiles/tester.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/tester.dir/depend

