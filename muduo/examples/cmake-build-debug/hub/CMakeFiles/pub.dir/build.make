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
CMAKE_BINARY_DIR = /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug

# Include any dependencies generated for this target.
include hub/CMakeFiles/pub.dir/depend.make

# Include the progress variables for this target.
include hub/CMakeFiles/pub.dir/progress.make

# Include the compile flags for this target's objects.
include hub/CMakeFiles/pub.dir/flags.make

hub/CMakeFiles/pub.dir/pub.cc.o: hub/CMakeFiles/pub.dir/flags.make
hub/CMakeFiles/pub.dir/pub.cc.o: ../hub/pub.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object hub/CMakeFiles/pub.dir/pub.cc.o"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pub.dir/pub.cc.o -c /home/onter/project/hub/demohub/muduo/examples/hub/pub.cc

hub/CMakeFiles/pub.dir/pub.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pub.dir/pub.cc.i"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/examples/hub/pub.cc > CMakeFiles/pub.dir/pub.cc.i

hub/CMakeFiles/pub.dir/pub.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pub.dir/pub.cc.s"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/examples/hub/pub.cc -o CMakeFiles/pub.dir/pub.cc.s

hub/CMakeFiles/pub.dir/pub.cc.o.requires:

.PHONY : hub/CMakeFiles/pub.dir/pub.cc.o.requires

hub/CMakeFiles/pub.dir/pub.cc.o.provides: hub/CMakeFiles/pub.dir/pub.cc.o.requires
	$(MAKE) -f hub/CMakeFiles/pub.dir/build.make hub/CMakeFiles/pub.dir/pub.cc.o.provides.build
.PHONY : hub/CMakeFiles/pub.dir/pub.cc.o.provides

hub/CMakeFiles/pub.dir/pub.cc.o.provides.build: hub/CMakeFiles/pub.dir/pub.cc.o


# Object files for target pub
pub_OBJECTS = \
"CMakeFiles/pub.dir/pub.cc.o"

# External object files for target pub
pub_EXTERNAL_OBJECTS =

hub/pub: hub/CMakeFiles/pub.dir/pub.cc.o
hub/pub: hub/CMakeFiles/pub.dir/build.make
hub/pub: hub/libmuduo_pubsub.a
hub/pub: hub/CMakeFiles/pub.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pub"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pub.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hub/CMakeFiles/pub.dir/build: hub/pub

.PHONY : hub/CMakeFiles/pub.dir/build

hub/CMakeFiles/pub.dir/requires: hub/CMakeFiles/pub.dir/pub.cc.o.requires

.PHONY : hub/CMakeFiles/pub.dir/requires

hub/CMakeFiles/pub.dir/clean:
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && $(CMAKE_COMMAND) -P CMakeFiles/pub.dir/cmake_clean.cmake
.PHONY : hub/CMakeFiles/pub.dir/clean

hub/CMakeFiles/pub.dir/depend:
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onter/project/hub/demohub/muduo/examples /home/onter/project/hub/demohub/muduo/examples/hub /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub/CMakeFiles/pub.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hub/CMakeFiles/pub.dir/depend
