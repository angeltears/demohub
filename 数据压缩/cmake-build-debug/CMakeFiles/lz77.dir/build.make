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
include CMakeFiles/lz77.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lz77.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lz77.dir/flags.make

CMakeFiles/lz77.dir/lz77.cc.o: CMakeFiles/lz77.dir/flags.make
CMakeFiles/lz77.dir/lz77.cc.o: ../lz77.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/数据压缩/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lz77.dir/lz77.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lz77.dir/lz77.cc.o -c /home/onter/project/hub/demohub/数据压缩/lz77.cc

CMakeFiles/lz77.dir/lz77.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lz77.dir/lz77.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/数据压缩/lz77.cc > CMakeFiles/lz77.dir/lz77.cc.i

CMakeFiles/lz77.dir/lz77.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lz77.dir/lz77.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/数据压缩/lz77.cc -o CMakeFiles/lz77.dir/lz77.cc.s

CMakeFiles/lz77.dir/lz77.cc.o.requires:

.PHONY : CMakeFiles/lz77.dir/lz77.cc.o.requires

CMakeFiles/lz77.dir/lz77.cc.o.provides: CMakeFiles/lz77.dir/lz77.cc.o.requires
	$(MAKE) -f CMakeFiles/lz77.dir/build.make CMakeFiles/lz77.dir/lz77.cc.o.provides.build
.PHONY : CMakeFiles/lz77.dir/lz77.cc.o.provides

CMakeFiles/lz77.dir/lz77.cc.o.provides.build: CMakeFiles/lz77.dir/lz77.cc.o


# Object files for target lz77
lz77_OBJECTS = \
"CMakeFiles/lz77.dir/lz77.cc.o"

# External object files for target lz77
lz77_EXTERNAL_OBJECTS =

liblz77.a: CMakeFiles/lz77.dir/lz77.cc.o
liblz77.a: CMakeFiles/lz77.dir/build.make
liblz77.a: CMakeFiles/lz77.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onter/project/hub/demohub/数据压缩/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblz77.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lz77.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lz77.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lz77.dir/build: liblz77.a

.PHONY : CMakeFiles/lz77.dir/build

CMakeFiles/lz77.dir/requires: CMakeFiles/lz77.dir/lz77.cc.o.requires

.PHONY : CMakeFiles/lz77.dir/requires

CMakeFiles/lz77.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lz77.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lz77.dir/clean

CMakeFiles/lz77.dir/depend:
	cd /home/onter/project/hub/demohub/数据压缩/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onter/project/hub/demohub/数据压缩 /home/onter/project/hub/demohub/数据压缩 /home/onter/project/hub/demohub/数据压缩/cmake-build-debug /home/onter/project/hub/demohub/数据压缩/cmake-build-debug /home/onter/project/hub/demohub/数据压缩/cmake-build-debug/CMakeFiles/lz77.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lz77.dir/depend

