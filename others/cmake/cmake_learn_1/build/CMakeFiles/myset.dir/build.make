# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/ubuntu/vscode/cmake/cmake_learn_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/vscode/cmake/cmake_learn_1/build

# Include any dependencies generated for this target.
include CMakeFiles/myset.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/myset.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myset.dir/flags.make

CMakeFiles/myset.dir/myset.cpp.o: CMakeFiles/myset.dir/flags.make
CMakeFiles/myset.dir/myset.cpp.o: ../myset.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/vscode/cmake/cmake_learn_1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myset.dir/myset.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myset.dir/myset.cpp.o -c /home/ubuntu/vscode/cmake/cmake_learn_1/myset.cpp

CMakeFiles/myset.dir/myset.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myset.dir/myset.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/vscode/cmake/cmake_learn_1/myset.cpp > CMakeFiles/myset.dir/myset.cpp.i

CMakeFiles/myset.dir/myset.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myset.dir/myset.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/vscode/cmake/cmake_learn_1/myset.cpp -o CMakeFiles/myset.dir/myset.cpp.s

CMakeFiles/myset.dir/myset.cpp.o.requires:

.PHONY : CMakeFiles/myset.dir/myset.cpp.o.requires

CMakeFiles/myset.dir/myset.cpp.o.provides: CMakeFiles/myset.dir/myset.cpp.o.requires
	$(MAKE) -f CMakeFiles/myset.dir/build.make CMakeFiles/myset.dir/myset.cpp.o.provides.build
.PHONY : CMakeFiles/myset.dir/myset.cpp.o.provides

CMakeFiles/myset.dir/myset.cpp.o.provides.build: CMakeFiles/myset.dir/myset.cpp.o


# Object files for target myset
myset_OBJECTS = \
"CMakeFiles/myset.dir/myset.cpp.o"

# External object files for target myset
myset_EXTERNAL_OBJECTS =

libmyset.a: CMakeFiles/myset.dir/myset.cpp.o
libmyset.a: CMakeFiles/myset.dir/build.make
libmyset.a: CMakeFiles/myset.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/vscode/cmake/cmake_learn_1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmyset.a"
	$(CMAKE_COMMAND) -P CMakeFiles/myset.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myset.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myset.dir/build: libmyset.a

.PHONY : CMakeFiles/myset.dir/build

CMakeFiles/myset.dir/requires: CMakeFiles/myset.dir/myset.cpp.o.requires

.PHONY : CMakeFiles/myset.dir/requires

CMakeFiles/myset.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myset.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myset.dir/clean

CMakeFiles/myset.dir/depend:
	cd /home/ubuntu/vscode/cmake/cmake_learn_1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/vscode/cmake/cmake_learn_1 /home/ubuntu/vscode/cmake/cmake_learn_1 /home/ubuntu/vscode/cmake/cmake_learn_1/build /home/ubuntu/vscode/cmake/cmake_learn_1/build /home/ubuntu/vscode/cmake/cmake_learn_1/build/CMakeFiles/myset.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myset.dir/depend

