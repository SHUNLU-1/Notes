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
CMAKE_SOURCE_DIR = /home/ubuntu/vscode/cmake/cmake_learn_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/vscode/cmake/cmake_learn_3/build

# Include any dependencies generated for this target.
include CMakeFiles/CalculateSqrt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CalculateSqrt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CalculateSqrt.dir/flags.make

CMakeFiles/CalculateSqrt.dir/hello.c.o: CMakeFiles/CalculateSqrt.dir/flags.make
CMakeFiles/CalculateSqrt.dir/hello.c.o: ../hello.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/vscode/cmake/cmake_learn_3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CalculateSqrt.dir/hello.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CalculateSqrt.dir/hello.c.o   -c /home/ubuntu/vscode/cmake/cmake_learn_3/hello.c

CMakeFiles/CalculateSqrt.dir/hello.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CalculateSqrt.dir/hello.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ubuntu/vscode/cmake/cmake_learn_3/hello.c > CMakeFiles/CalculateSqrt.dir/hello.c.i

CMakeFiles/CalculateSqrt.dir/hello.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CalculateSqrt.dir/hello.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ubuntu/vscode/cmake/cmake_learn_3/hello.c -o CMakeFiles/CalculateSqrt.dir/hello.c.s

CMakeFiles/CalculateSqrt.dir/hello.c.o.requires:

.PHONY : CMakeFiles/CalculateSqrt.dir/hello.c.o.requires

CMakeFiles/CalculateSqrt.dir/hello.c.o.provides: CMakeFiles/CalculateSqrt.dir/hello.c.o.requires
	$(MAKE) -f CMakeFiles/CalculateSqrt.dir/build.make CMakeFiles/CalculateSqrt.dir/hello.c.o.provides.build
.PHONY : CMakeFiles/CalculateSqrt.dir/hello.c.o.provides

CMakeFiles/CalculateSqrt.dir/hello.c.o.provides.build: CMakeFiles/CalculateSqrt.dir/hello.c.o


# Object files for target CalculateSqrt
CalculateSqrt_OBJECTS = \
"CMakeFiles/CalculateSqrt.dir/hello.c.o"

# External object files for target CalculateSqrt
CalculateSqrt_EXTERNAL_OBJECTS =

CalculateSqrt: CMakeFiles/CalculateSqrt.dir/hello.c.o
CalculateSqrt: CMakeFiles/CalculateSqrt.dir/build.make
CalculateSqrt: CMakeFiles/CalculateSqrt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/vscode/cmake/cmake_learn_3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CalculateSqrt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CalculateSqrt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CalculateSqrt.dir/build: CalculateSqrt

.PHONY : CMakeFiles/CalculateSqrt.dir/build

CMakeFiles/CalculateSqrt.dir/requires: CMakeFiles/CalculateSqrt.dir/hello.c.o.requires

.PHONY : CMakeFiles/CalculateSqrt.dir/requires

CMakeFiles/CalculateSqrt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CalculateSqrt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CalculateSqrt.dir/clean

CMakeFiles/CalculateSqrt.dir/depend:
	cd /home/ubuntu/vscode/cmake/cmake_learn_3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/vscode/cmake/cmake_learn_3 /home/ubuntu/vscode/cmake/cmake_learn_3 /home/ubuntu/vscode/cmake/cmake_learn_3/build /home/ubuntu/vscode/cmake/cmake_learn_3/build /home/ubuntu/vscode/cmake/cmake_learn_3/build/CMakeFiles/CalculateSqrt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CalculateSqrt.dir/depend

