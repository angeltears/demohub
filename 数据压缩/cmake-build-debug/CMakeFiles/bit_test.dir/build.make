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
CMAKE_SOURCE_DIR = /home/onter/project/hub/demohub/数据压缩

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/onter/project/hub/demohub/数据压缩/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bit_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bit_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bit_test.dir/flags.make

CMakeFiles/bit_test.dir/bit_test.cc.o: CMakeFiles/bit_test.dir/flags.make
CMakeFiles/bit_test.dir/bit_test.cc.o: ../bit_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/数据压缩/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bit_test.dir/bit_test.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bit_test.dir/bit_test.cc.o -c /home/onter/project/hub/demohub/数据压缩/bit_test.cc

CMakeFiles/bit_test.dir/bit_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bit_test.dir/bit_test.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/数据压缩/bit_test.cc > CMakeFiles/bit_test.dir/bit_test.cc.i

CMakeFiles/bit_test.dir/bit_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bit_test.dir/bit_test.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/数据压缩/bit_test.cc -o CMakeFiles/bit_test.dir/bit_test.cc.s

CMakeFiles/bit_test.dir/bit_test.cc.o.requires:

.PHONY : CMakeFiles/bit_test.dir/bit_test.cc.o.requires

CMakeFiles/bit_test.dir/bit_test.cc.o.provides: CMakeFiles/bit_test.dir/bit_test.cc.o.requires
	$(MAKE) -f CMakeFiles/bit_test.dir/build.make CMakeFiles/bit_test.dir/bit_test.cc.o.provides.build
.PHONY : CMakeFiles/bit_test.dir/bit_test.cc.o.provides

CMakeFiles/bit_test.dir/bit_test.cc.o.provides.build: CMakeFiles/bit_test.dir/bit_test.cc.o


# Object files for target bit_test
bit_test_OBJECTS = \
"CMakeFiles/bit_test.dir/bit_test.cc.o"

# External object files for target bit_test
bit_test_EXTERNAL_OBJECTS =

bit_test: CMakeFiles/bit_test.dir/bit_test.cc.o
bit_test: CMakeFiles/bit_test.dir/build.make
bit_test: libds.a
bit_test: CMakeFiles/bit_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onter/project/hub/demohub/数据压缩/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bit_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bit_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bit_test.dir/build: bit_test

.PHONY : CMakeFiles/bit_test.dir/build

CMakeFiles/bit_test.dir/requires: CMakeFiles/bit_test.dir/bit_test.cc.o.requires

.PHONY : CMakeFiles/bit_test.dir/requires

CMakeFiles/bit_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bit_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bit_test.dir/clean

CMakeFiles/bit_test.dir/depend:
	cd /home/onter/project/hub/demohub/数据压缩/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onter/project/hub/demohub/数据压缩 /home/onter/project/hub/demohub/数据压缩 /home/onter/project/hub/demohub/数据压缩/cmake-build-debug /home/onter/project/hub/demohub/数据压缩/cmake-build-debug /home/onter/project/hub/demohub/数据压缩/cmake-build-debug/CMakeFiles/bit_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bit_test.dir/depend

