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
CMAKE_SOURCE_DIR = /home/onter/project/hub/demohub/thread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/onter/project/hub/demohub/thread/cmake-build-debug

# Include any dependencies generated for this target.
include 2/CMakeFiles/oops.dir/depend.make

# Include the progress variables for this target.
include 2/CMakeFiles/oops.dir/progress.make

# Include the compile flags for this target's objects.
include 2/CMakeFiles/oops.dir/flags.make

2/CMakeFiles/oops.dir/oops.cc.o: 2/CMakeFiles/oops.dir/flags.make
2/CMakeFiles/oops.dir/oops.cc.o: ../2/oops.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/thread/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 2/CMakeFiles/oops.dir/oops.cc.o"
	cd /home/onter/project/hub/demohub/thread/cmake-build-debug/2 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/oops.dir/oops.cc.o -c /home/onter/project/hub/demohub/thread/2/oops.cc

2/CMakeFiles/oops.dir/oops.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oops.dir/oops.cc.i"
	cd /home/onter/project/hub/demohub/thread/cmake-build-debug/2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/thread/2/oops.cc > CMakeFiles/oops.dir/oops.cc.i

2/CMakeFiles/oops.dir/oops.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oops.dir/oops.cc.s"
	cd /home/onter/project/hub/demohub/thread/cmake-build-debug/2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/thread/2/oops.cc -o CMakeFiles/oops.dir/oops.cc.s

2/CMakeFiles/oops.dir/oops.cc.o.requires:

.PHONY : 2/CMakeFiles/oops.dir/oops.cc.o.requires

2/CMakeFiles/oops.dir/oops.cc.o.provides: 2/CMakeFiles/oops.dir/oops.cc.o.requires
	$(MAKE) -f 2/CMakeFiles/oops.dir/build.make 2/CMakeFiles/oops.dir/oops.cc.o.provides.build
.PHONY : 2/CMakeFiles/oops.dir/oops.cc.o.provides

2/CMakeFiles/oops.dir/oops.cc.o.provides.build: 2/CMakeFiles/oops.dir/oops.cc.o


# Object files for target oops
oops_OBJECTS = \
"CMakeFiles/oops.dir/oops.cc.o"

# External object files for target oops
oops_EXTERNAL_OBJECTS =

2/oops: 2/CMakeFiles/oops.dir/oops.cc.o
2/oops: 2/CMakeFiles/oops.dir/build.make
2/oops: 2/CMakeFiles/oops.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onter/project/hub/demohub/thread/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable oops"
	cd /home/onter/project/hub/demohub/thread/cmake-build-debug/2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oops.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
2/CMakeFiles/oops.dir/build: 2/oops

.PHONY : 2/CMakeFiles/oops.dir/build

2/CMakeFiles/oops.dir/requires: 2/CMakeFiles/oops.dir/oops.cc.o.requires

.PHONY : 2/CMakeFiles/oops.dir/requires

2/CMakeFiles/oops.dir/clean:
	cd /home/onter/project/hub/demohub/thread/cmake-build-debug/2 && $(CMAKE_COMMAND) -P CMakeFiles/oops.dir/cmake_clean.cmake
.PHONY : 2/CMakeFiles/oops.dir/clean

2/CMakeFiles/oops.dir/depend:
	cd /home/onter/project/hub/demohub/thread/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onter/project/hub/demohub/thread /home/onter/project/hub/demohub/thread/2 /home/onter/project/hub/demohub/thread/cmake-build-debug /home/onter/project/hub/demohub/thread/cmake-build-debug/2 /home/onter/project/hub/demohub/thread/cmake-build-debug/2/CMakeFiles/oops.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 2/CMakeFiles/oops.dir/depend

