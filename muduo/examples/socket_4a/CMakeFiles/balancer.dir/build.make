# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/onter/software/clion-2017.3.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/onter/software/clion-2017.3.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/onter/project/hub/demohub/muduo/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/onter/project/hub/demohub/muduo/examples

# Include any dependencies generated for this target.
include socket_4a/CMakeFiles/balancer.dir/depend.make

# Include the progress variables for this target.
include socket_4a/CMakeFiles/balancer.dir/progress.make

# Include the compile flags for this target's objects.
include socket_4a/CMakeFiles/balancer.dir/flags.make

socket_4a/CMakeFiles/balancer.dir/balancer.cc.o: socket_4a/CMakeFiles/balancer.dir/flags.make
socket_4a/CMakeFiles/balancer.dir/balancer.cc.o: socket_4a/balancer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object socket_4a/CMakeFiles/balancer.dir/balancer.cc.o"
	cd /home/onter/project/hub/demohub/muduo/examples/socket_4a && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/balancer.dir/balancer.cc.o -c /home/onter/project/hub/demohub/muduo/examples/socket_4a/balancer.cc

socket_4a/CMakeFiles/balancer.dir/balancer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/balancer.dir/balancer.cc.i"
	cd /home/onter/project/hub/demohub/muduo/examples/socket_4a && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/examples/socket_4a/balancer.cc > CMakeFiles/balancer.dir/balancer.cc.i

socket_4a/CMakeFiles/balancer.dir/balancer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/balancer.dir/balancer.cc.s"
	cd /home/onter/project/hub/demohub/muduo/examples/socket_4a && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/examples/socket_4a/balancer.cc -o CMakeFiles/balancer.dir/balancer.cc.s

socket_4a/CMakeFiles/balancer.dir/balancer.cc.o.requires:

.PHONY : socket_4a/CMakeFiles/balancer.dir/balancer.cc.o.requires

socket_4a/CMakeFiles/balancer.dir/balancer.cc.o.provides: socket_4a/CMakeFiles/balancer.dir/balancer.cc.o.requires
	$(MAKE) -f socket_4a/CMakeFiles/balancer.dir/build.make socket_4a/CMakeFiles/balancer.dir/balancer.cc.o.provides.build
.PHONY : socket_4a/CMakeFiles/balancer.dir/balancer.cc.o.provides

socket_4a/CMakeFiles/balancer.dir/balancer.cc.o.provides.build: socket_4a/CMakeFiles/balancer.dir/balancer.cc.o


# Object files for target balancer
balancer_OBJECTS = \
"CMakeFiles/balancer.dir/balancer.cc.o"

# External object files for target balancer
balancer_EXTERNAL_OBJECTS =

socket_4a/balancer: socket_4a/CMakeFiles/balancer.dir/balancer.cc.o
socket_4a/balancer: socket_4a/CMakeFiles/balancer.dir/build.make
socket_4a/balancer: socket_4a/CMakeFiles/balancer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onter/project/hub/demohub/muduo/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable balancer"
	cd /home/onter/project/hub/demohub/muduo/examples/socket_4a && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/balancer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
socket_4a/CMakeFiles/balancer.dir/build: socket_4a/balancer

.PHONY : socket_4a/CMakeFiles/balancer.dir/build

socket_4a/CMakeFiles/balancer.dir/requires: socket_4a/CMakeFiles/balancer.dir/balancer.cc.o.requires

.PHONY : socket_4a/CMakeFiles/balancer.dir/requires

socket_4a/CMakeFiles/balancer.dir/clean:
	cd /home/onter/project/hub/demohub/muduo/examples/socket_4a && $(CMAKE_COMMAND) -P CMakeFiles/balancer.dir/cmake_clean.cmake
.PHONY : socket_4a/CMakeFiles/balancer.dir/clean

socket_4a/CMakeFiles/balancer.dir/depend:
	cd /home/onter/project/hub/demohub/muduo/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onter/project/hub/demohub/muduo/examples /home/onter/project/hub/demohub/muduo/examples/socket_4a /home/onter/project/hub/demohub/muduo/examples /home/onter/project/hub/demohub/muduo/examples/socket_4a /home/onter/project/hub/demohub/muduo/examples/socket_4a/CMakeFiles/balancer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : socket_4a/CMakeFiles/balancer.dir/depend

