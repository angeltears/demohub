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
include hub/CMakeFiles/muduo_pubsub.dir/depend.make

# Include the progress variables for this target.
include hub/CMakeFiles/muduo_pubsub.dir/progress.make

# Include the compile flags for this target's objects.
include hub/CMakeFiles/muduo_pubsub.dir/flags.make

hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o: hub/CMakeFiles/muduo_pubsub.dir/flags.make
hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o: ../hub/pubsub.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_pubsub.dir/pubsub.cc.o -c /home/onter/project/hub/demohub/muduo/examples/hub/pubsub.cc

hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_pubsub.dir/pubsub.cc.i"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/examples/hub/pubsub.cc > CMakeFiles/muduo_pubsub.dir/pubsub.cc.i

hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_pubsub.dir/pubsub.cc.s"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/examples/hub/pubsub.cc -o CMakeFiles/muduo_pubsub.dir/pubsub.cc.s

hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o.requires:

.PHONY : hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o.requires

hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o.provides: hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o.requires
	$(MAKE) -f hub/CMakeFiles/muduo_pubsub.dir/build.make hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o.provides.build
.PHONY : hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o.provides

hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o.provides.build: hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o


hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o: hub/CMakeFiles/muduo_pubsub.dir/flags.make
hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o: ../hub/codec.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_pubsub.dir/codec.cc.o -c /home/onter/project/hub/demohub/muduo/examples/hub/codec.cc

hub/CMakeFiles/muduo_pubsub.dir/codec.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_pubsub.dir/codec.cc.i"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/examples/hub/codec.cc > CMakeFiles/muduo_pubsub.dir/codec.cc.i

hub/CMakeFiles/muduo_pubsub.dir/codec.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_pubsub.dir/codec.cc.s"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/examples/hub/codec.cc -o CMakeFiles/muduo_pubsub.dir/codec.cc.s

hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o.requires:

.PHONY : hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o.requires

hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o.provides: hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o.requires
	$(MAKE) -f hub/CMakeFiles/muduo_pubsub.dir/build.make hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o.provides.build
.PHONY : hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o.provides

hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o.provides.build: hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o


# Object files for target muduo_pubsub
muduo_pubsub_OBJECTS = \
"CMakeFiles/muduo_pubsub.dir/pubsub.cc.o" \
"CMakeFiles/muduo_pubsub.dir/codec.cc.o"

# External object files for target muduo_pubsub
muduo_pubsub_EXTERNAL_OBJECTS =

hub/libmuduo_pubsub.a: hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o
hub/libmuduo_pubsub.a: hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o
hub/libmuduo_pubsub.a: hub/CMakeFiles/muduo_pubsub.dir/build.make
hub/libmuduo_pubsub.a: hub/CMakeFiles/muduo_pubsub.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmuduo_pubsub.a"
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && $(CMAKE_COMMAND) -P CMakeFiles/muduo_pubsub.dir/cmake_clean_target.cmake
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/muduo_pubsub.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hub/CMakeFiles/muduo_pubsub.dir/build: hub/libmuduo_pubsub.a

.PHONY : hub/CMakeFiles/muduo_pubsub.dir/build

hub/CMakeFiles/muduo_pubsub.dir/requires: hub/CMakeFiles/muduo_pubsub.dir/pubsub.cc.o.requires
hub/CMakeFiles/muduo_pubsub.dir/requires: hub/CMakeFiles/muduo_pubsub.dir/codec.cc.o.requires

.PHONY : hub/CMakeFiles/muduo_pubsub.dir/requires

hub/CMakeFiles/muduo_pubsub.dir/clean:
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub && $(CMAKE_COMMAND) -P CMakeFiles/muduo_pubsub.dir/cmake_clean.cmake
.PHONY : hub/CMakeFiles/muduo_pubsub.dir/clean

hub/CMakeFiles/muduo_pubsub.dir/depend:
	cd /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onter/project/hub/demohub/muduo/examples /home/onter/project/hub/demohub/muduo/examples/hub /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub /home/onter/project/hub/demohub/muduo/examples/cmake-build-debug/hub/CMakeFiles/muduo_pubsub.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hub/CMakeFiles/muduo_pubsub.dir/depend

