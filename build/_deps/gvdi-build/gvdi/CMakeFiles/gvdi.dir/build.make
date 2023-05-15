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
CMAKE_SOURCE_DIR = /home/arvk/Code/cpp/Pixie

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arvk/Code/cpp/Pixie/build

# Include any dependencies generated for this target.
include _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/flags.make

_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/src/gvdi.cpp.o: _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/flags.make
_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/src/gvdi.cpp.o: _deps/gvdi-src/gvdi/src/gvdi.cpp
_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/src/gvdi.cpp.o: _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arvk/Code/cpp/Pixie/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/src/gvdi.cpp.o"
	cd /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build/gvdi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/src/gvdi.cpp.o -MF CMakeFiles/gvdi.dir/src/gvdi.cpp.o.d -o CMakeFiles/gvdi.dir/src/gvdi.cpp.o -c /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-src/gvdi/src/gvdi.cpp

_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/src/gvdi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gvdi.dir/src/gvdi.cpp.i"
	cd /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build/gvdi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-src/gvdi/src/gvdi.cpp > CMakeFiles/gvdi.dir/src/gvdi.cpp.i

_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/src/gvdi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gvdi.dir/src/gvdi.cpp.s"
	cd /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build/gvdi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-src/gvdi/src/gvdi.cpp -o CMakeFiles/gvdi.dir/src/gvdi.cpp.s

# Object files for target gvdi
gvdi_OBJECTS = \
"CMakeFiles/gvdi.dir/src/gvdi.cpp.o"

# External object files for target gvdi
gvdi_EXTERNAL_OBJECTS =

_deps/gvdi-build/gvdi/libgvdi.a: _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/src/gvdi.cpp.o
_deps/gvdi-build/gvdi/libgvdi.a: _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/build.make
_deps/gvdi-build/gvdi/libgvdi.a: _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arvk/Code/cpp/Pixie/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgvdi.a"
	cd /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build/gvdi && $(CMAKE_COMMAND) -P CMakeFiles/gvdi.dir/cmake_clean_target.cmake
	cd /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build/gvdi && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gvdi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/build: _deps/gvdi-build/gvdi/libgvdi.a
.PHONY : _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/build

_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/clean:
	cd /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build/gvdi && $(CMAKE_COMMAND) -P CMakeFiles/gvdi.dir/cmake_clean.cmake
.PHONY : _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/clean

_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/depend:
	cd /home/arvk/Code/cpp/Pixie/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arvk/Code/cpp/Pixie /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-src/gvdi /home/arvk/Code/cpp/Pixie/build /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build/gvdi /home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/gvdi-build/gvdi/CMakeFiles/gvdi.dir/depend

